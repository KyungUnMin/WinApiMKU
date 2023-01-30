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



//레벨의 지형과 충돌체를 로드하는 함수
void RoundLevelBase::LoadObstacle(const std::string_view& _RoundName, int _X, int _Y)
{
	//모든 RoundLevel의 Obstacle은 한 폴더에 저장되어 있다
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("Obstacle");

	//레벨 충돌체 Load
	//"Round" + _RoundName + "_Collider.bmp"
	ImageName += _RoundName.data();
	ColliderImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName + "_Collider.bmp"));
	ColliderImage->Cut(_X, _Y);

	//레벨 지형 이미지 로드
	//"Round" + _RoundName + "_Obstacle.bmp"
	ImageName += "_Obstacle.bmp";
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName))->Cut(_X, _Y);

	Obstacles = CreateActor<BackGround>();
	Obstacles->RenderReserve(_X * _Y);
}


//레벨의 지형을 생성하는 함수
void RoundLevelBase::CreateObstacle(const float4& _ArrangeDir, int _Order)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//지형 생성후 꺼두기
	for (size_t i = 0; i < Obstacles->GetRenderCapacity(); ++i)
	{
		GameEngineRender* Render = Obstacles->CreateRender(ImageName, _Order);
		Render->SetFrame(static_cast<int>(i));
		Render->Off();
	}

	//인자로 받은 _ArrangeDir방향으로 0번 Render가 화면 중앙에 나오게 정렬(0번 Render는 On)
	ArrangeStage(_ArrangeDir, 0);

	//Stage가 전환될때 Stage이동방향 설정
	MoveDir = -(_ArrangeDir);
}


//인자로 받은 _Dir방향으로 _CenterIndex번 Render가 화면 중앙에 나오게 정렬(_CenterIndex번 Render는 On)
void RoundLevelBase::ArrangeStage(float4 _Dir, size_t _CenterIndex)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	for (size_t i = 0; i < Obstacles->GetRenderSize(); ++i)
	{
		GameEngineRender* Render = Obstacles->GetRender(i);
		float4 Offset = float4::Zero;

		//정렬 방향이 오른쪽일때
		if (_Dir == float4::Right)
		{
			//_CenterIndex가 화면중앙에 나오게 정렬
			Offset = _Dir * ScreenSize.x * static_cast<float>(i - _CenterIndex);
		}

		//정렬 방향이 아래일때
		else if (_Dir == float4::Down)
		{
			//_CenterIndex가 화면중앙에 나오게 정렬
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

	//_CenterIndex번 Render만 On
	Obstacles->GetRender(NowIndex)->On();
}


//다음 Stage로 이동하는 함수
bool RoundLevelBase::MoveToNextStage()
{
	//이미 Stage가 이동중이라면 Return
	if (true == IsMoving)
		return false;

	//이번 스테이지가 마지막이였다면 false를 리턴
	if (NowIndex + 1 == Obstacles->GetRenderSize())
	{
		return false;
	}

	//IsMoving이 true일때 Update에서 Stage가 이동함
	IsMoving = true;

	//다음 Stage의 렌더러 On
	Obstacles->GetRender(NowIndex + 1)->On();
	return true;
}



void RoundLevelBase::Update(float _DeltaTime)
{
	//IsMoving이 true일때만 Stage가 이동함
	if (false == IsMoving)
		return;

	//모든 스테이지들이 이동
	for (size_t i = 0; i < Obstacles->GetRenderSize(); ++i)
	{
		GameEngineRender* Render = Obstacles->GetRender(i);
		float4 Offset = Render->GetPosition();
		Offset += MoveDir * MoveSpeed * _DeltaTime;
		Render->SetPosition(Offset);
	}

	//다음 스테이지의 Render
	GameEngineRender* NextStage = Obstacles->GetRender(NowIndex + 1);

	//다음 스테이지의 Offset이 화면 중심보다도 더 움직였다면 return 아래 코드 동작
	float4 NextOffset = NextStage->GetPosition();
	if (0 <= NextOffset.x && 0 <= NextOffset.y)
		return;

	//다음 Stage를 중심으로 Stage를 정렬하고 NowIndex를 1증가시키며 나머지 Render는 Off
	ArrangeStage(-MoveDir, NowIndex + 1);
	IsMoving = false;
}



//NowIndex가 현재 Round에서 마지막 Stage인지 알려주는 함수
bool RoundLevelBase::IsLastStage()
{
	return (NowIndex + 1) == Obstacles->GetRenderSize();
}


//인자로 받는 _Pos가 레벨의 지형에 의해 막힌 곳인지 알려주는 함수
bool RoundLevelBase::IsBlockPos(const float4& _Pos)
{
	//현재 Stage에 맞게 Offset을 조정	(3번 스테이지라면 해상도.x * 3)
	float4 Offset = ColliderImage->GetCutData(static_cast<int>(NowIndex)).GetStartPos();

	//해당 지점의 색상 추출
	DWORD Color = ColliderImage->GetPixelColor(Offset + _Pos, RGB(0, 0, 0));

	//검정색이라면 맵의 충돌체에 막혀있는곳
	return Color == RGB(0,0,0);
}


//PlayerCharacterType 타입에 따라 플레이어를 생성하는 함수
void RoundLevelBase::CreatePlayer(PlayerCharacterType _Type)
{
	SelectedCharacter = _Type;

	//이미 그 플레이어가 존재한다면(ReStart 한 경우 이미 존재할 수도 있음)
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


//레벨이 전환될때 레벨 정리하고 가기
void RoundLevelBase::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	IsMoving = false; 

	RoundLevelBase* NextRoundLevel = dynamic_cast<RoundLevelBase*>(_NextLevel);

	//다음레벨이 Round레벨이 아닌경우
	if (nullptr == NextRoundLevel)
		return;

	//다음 레벨에 플레이어 생성시키기
	NextRoundLevel->CreatePlayer(SelectedCharacter);
}
