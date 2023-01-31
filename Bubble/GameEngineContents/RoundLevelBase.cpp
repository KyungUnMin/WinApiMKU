#include "RoundLevelBase.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BackGround.h"
#include "Player_Bubblun.h"
#include "Player_Bobblun.h"
#include "Player_Kululun.h"
#include "Player_Cororon.h"

const float RoundLevelBase::StageMoveDuration = 1.5f;

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
	//지형 생성후 꺼두기
	for (size_t i = 0; i < Obstacles->GetRenderCapacity(); ++i)
	{
		GameEngineRender* Render = Obstacles->CreateRender(ImageName, _Order);
		Render->SetFrame(static_cast<int>(i));
		Render->Off();
	}

	if ((_ArrangeDir != float4::Right) && (_ArrangeDir != float4::Down))
	{
		MsgAssert("float4::Right 또는 float4::Down 방향으로만 지형을 나열할 수 있습니다.");
		return;
	}

	ArrangeDir = _ArrangeDir;

	//첫번째 스테이지 화면 정 중앙에 설정
	Obstacles->GetRender(0)->SetPosition(float4::Zero);
	Obstacles->GetRender(0)->On();
}



//다음 Stage로 이동하는 함수
bool RoundLevelBase::MoveToNextStage()
{
	//이미 Stage가 이동중이라면 Return
	if (true == IsMoveValue)
		return false;

	//이번 스테이지가 마지막이였다면 false를 리턴
	if (NowIndex + 1 == Obstacles->GetRenderSize())
	{
		return false;
	}


	//IsMoveValue이 true일때 Update에서 Stage가 이동함
	IsMoveValue = true;

	//다음 Stage의 렌더러 On
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	GameEngineRender* NextRender = Obstacles->GetRender(NowIndex + 1);
	NextRender->On();
	NextRender->SetPosition(-ArrangeDir * ScreenSize);

	return true;
}





void RoundLevelBase::Update(float _DeltaTime)
{
	//IsMoving이 true일때만 Stage가 이동함
	if (false == IsMoveValue)
		return;

	//StageMoveDurationt 시간안에 Stage전환
	StageMoveTime += _DeltaTime;
	float Ratio = StageMoveTime / StageMoveDuration;

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//현재 스테이지
	{
		GameEngineRender* StageRender = Obstacles->GetRender(NowIndex);
		float4 StartPos = float4::Zero;
		float4 DestPos = -ArrangeDir * ScreenSize;
		float4 NowPos = float4::LerpClamp(StartPos, DestPos, Ratio);
		StageRender->SetPosition(NowPos);
	}

	//다음 스테이지
	{
		GameEngineRender* StageRender = Obstacles->GetRender(NowIndex + 1);
		float4 StartPos = ArrangeDir * ScreenSize;
		float4 DestPos = float4::Zero;
		float4 NowPos = float4::LerpClamp(StartPos, DestPos, Ratio);
		StageRender->SetPosition(NowPos);
	}

	//StageMoveDurationt을 경과했다면
	if (1.f < Ratio)
	{
		//ArrangeStage(ArrangeDir, NowIndex + 1);
		SetNowStage(NowIndex + 1);
		IsMoveValue = false;
		StageMoveTime = 0.f;
	}
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


void RoundLevelBase::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	RoundLevelBase* PrevRoundLevel = dynamic_cast<RoundLevelBase*>(_PrevLevel);

	//이전레벨이 Round레벨이 아닌경우
	if (nullptr == PrevRoundLevel)
	{
		//기본 캐릭터(초록색) 생성
		CreatePlayer(SelectedCharacter);
	}

	//이전레벨이 Round레벨인 경우 이전의 플레이어 타입에 따라 새 플레이어 생성
	else
	{
		CreatePlayer(PrevRoundLevel->GetSelectCharacter());
	}
}

//레벨이 전환될때 레벨 정리하고 가기
void RoundLevelBase::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	IsMoveValue = false;
	SetNowStage(0);
}

//현재 Round의 Stage를 강제로 설정하는 함수
void RoundLevelBase::SetNowStage(int _StageNum)
{
	//모든 스테이지 끄기
	for (size_t i = 0; i < Obstacles->GetRenderSize(); ++i)
	{
		Obstacles->GetRender(i)->Off();
	}

	//인자로 받은_StageNum만 켜기
	NowIndex = _StageNum;
	Obstacles->GetRender(NowIndex)->On();
	Obstacles->GetRender(NowIndex)->SetPosition(float4::Zero);
}
