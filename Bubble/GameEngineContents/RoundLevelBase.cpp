#include "RoundLevelBase.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BackGround.h"
#include "Player_Bubblun.h"
#include "Player_Bobblun.h"
#include "Player_Kululun.h"
#include "Player_Cororon.h"

RoundLevelBase::RoundLevelBase()
{

}

RoundLevelBase::~RoundLevelBase()
{

}




void RoundLevelBase::LoadObstacle(const std::string_view& _RoundName, int _X, int _Y)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("Obstacle");

	ImageName += _RoundName.data();
	ColliderImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName + "_Collider.bmp"));
	ColliderImage->Cut(_X, _Y);

	ImageName += "_Obstacle.bmp";
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName))->Cut(_X, _Y);

	Obstacles = CreateActor<BackGround>();
	Obstacles->RenderReserve(_X * _Y);
}



void RoundLevelBase::CreateObstacle(const float4& _ArrangeDir, int _Order)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	for (size_t i = 0; i < Obstacles->GetRenderCapacity(); ++i)
	{
		GameEngineRender* Render = Obstacles->CreateRender(ImageName, _Order);
		Render->SetFrame(static_cast<int>(i));
		Render->Off();
	}

	ArrangeStage(_ArrangeDir, 0);
	MoveDir = -(_ArrangeDir);
}

void RoundLevelBase::ArrangeStage(float4 _Dir, size_t _CenterIndex)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	for (size_t i = 0; i < Obstacles->GetRenderSize(); ++i)
	{
		GameEngineRender* Render = Obstacles->GetRender(i);
		float4 Offset = float4::Zero;

		if (_Dir == float4::Right)
		{
			Offset = _Dir * ScreenSize.x * static_cast<float>(i - _CenterIndex);
		}
		else if (_Dir == float4::Down)
		{
			Offset = _Dir * ScreenSize.y * static_cast<float>(i - _CenterIndex);
		}
		else
		{
			MsgAssert("float4::Right 또는 float4::Down 방향으로만 지형을 나열할 수 있습니다.");
		}

		Render->SetPosition(Offset);
		Render->Off();
	}

	NowIndex = _CenterIndex;
	Obstacles->GetRender(NowIndex)->On();
}



bool RoundLevelBase::MoveToNextStage()
{
	if (true == IsMoving)
		return false;

	if (NowIndex + 1 == Obstacles->GetRenderSize())
	{
		return false;
	}

	IsMoving = true;
	Obstacles->GetRender(NowIndex + 1)->On();
	return true;
}



void RoundLevelBase::Update(float _DeltaTime)
{
	if (false == IsMoving)
		return;

	for (size_t i = 0; i < Obstacles->GetRenderSize(); ++i)
	{
		GameEngineRender* Render = Obstacles->GetRender(i);
		float4 Offset = Render->GetPosition();
		Offset += MoveDir * MoveSpeed * _DeltaTime;
		Render->SetPosition(Offset);
	}

	//GameEngineRender* PrevStage = Obstacles->GetRender(NowIndex);
	GameEngineRender* NextStage = Obstacles->GetRender(NowIndex + 1);

	float4 NextOffset = NextStage->GetPosition();
	if (0 <= NextOffset.x && 0 <= NextOffset.y)
		return;

	ArrangeStage(-MoveDir, NowIndex + 1);
	/*PrevStage->Off();
	NowIndex = NowIndex + 1;*/
	IsMoving = false;
}




bool RoundLevelBase::IsLastStage()
{
	return (NowIndex + 1) == Obstacles->GetRenderSize();
}

bool RoundLevelBase::IsBlockPos(const float4& _Pos)
{
	float4 Offset = ColliderImage->GetCutData(static_cast<int>(NowIndex)).GetStartPos();
	DWORD Color = ColliderImage->GetPixelColor(Offset + _Pos, RGB(0, 0, 0));
	return Color == RGB(0,0,0);
}


void RoundLevelBase::CreatePlayer(PlayerCharacterType _Type)
{
	SelectedCharacter = _Type;

	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	switch (_Type)
	{
	case PlayerCharacterType::BUBBLUN:
		Player = CreateActor<Player_Bubblun>();
		break;
	case PlayerCharacterType::BOBBLUN:
		Player = CreateActor <Player_Bobblun>();
		break;
	case PlayerCharacterType::KULULUN:
		Player = CreateActor <Player_Kululun>();
		break;
	case PlayerCharacterType::CORORON:
		Player = CreateActor <Player_Cororon>();
		break;
	}

}

void RoundLevelBase::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	IsMoving = false; 
	

	RoundLevelBase* NextRoundLevel = dynamic_cast<RoundLevelBase*>(_NextLevel);

	//다음레벨이 Round레벨이 아닌경우
	if (nullptr == NextRoundLevel)
		return;

	NextRoundLevel->CreatePlayer(SelectedCharacter);
}
