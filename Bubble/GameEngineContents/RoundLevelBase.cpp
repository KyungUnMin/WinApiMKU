#include "RoundLevelBase.h"
#include <GameEngineBase/GameEngineDebug.h>
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
#include "BubbleSpawner.h"
#include "BubbleDestination.h"
#include "BubbleMissle.h"
#include "BubbleMissleFSM.h"
#include "BubbleDestHelper.h"
#include "MonsterSpawner.h"
#include "PointPannel.h"
#include "NatureMissleBase.h"
#include "BossDeadBox.h"
#include "BossDeadUI.h"
#include "NextDoor.h"
#include "BubbleCore.h"

const float4	RoundLevelBase::PlayerSpawnPos			= { 100.f, 620.f };
const float		RoundLevelBase::StageMoveDuration	= 1.5f;

RoundLevelBase::RoundLevelBase()
{

}

RoundLevelBase::~RoundLevelBase()
{
	for (size_t i = 0; i < MonsterSpawners.size(); ++i)
	{
		if (nullptr == MonsterSpawners[i])
			continue;

		delete MonsterSpawners[i];
		MonsterSpawners[i] = nullptr;
	}

	MonsterSpawners.clear();
}





void RoundLevelBase::Loading()
{
	DestHelperPtr = CreateActor<BubbleDestHelper>();
	BgmLoad();
	CreateActor<PointPannel>();
}




//레벨의 지형과 충돌체를 로드하는 함수
void RoundLevelBase::LoadStage(const std::string_view& _RoundName, int _X, int _Y)
{
	//모든 RoundLevel의 Obstacle은 한 폴더에 저장되어 있다
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("Stage");

	//레벨 충돌체 Load
	//"Round" + _RoundName + "_Collider.bmp"
	ImageName += _RoundName.data();


	StageCollision = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName + "_Collider.bmp"));
	StageCollision->Cut(_X, _Y);

	//레벨 지형 이미지 로드
	//"Round" + _RoundName + "_Obstacle.bmp"
	ImageName += "_Stage.bmp";
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName))->Cut(_X, _Y);

	StageImage = CreateActor<BackGround>();
	StageImage->RenderReserve(_X * _Y);

	CreateSpanwerPool(_X);
}

void RoundLevelBase::CreateSpanwerPool(int _StageCount)
{
	MonsterSpawners.resize(_StageCount, nullptr);
	for (size_t i = 0; i < MonsterSpawners.size(); ++i)
	{
		MonsterSpawners[i] = new MonsterSpawner(this);
	}
}

//레벨의 지형을 생성하는 함수
void RoundLevelBase::CreateStage(const float4& _ArrangeDir, int _Order)
{
	//지형 생성후 꺼두기
	for (size_t i = 0; i < StageImage->GetRenderCapacity(); ++i)
	{
		GameEngineRender* Render = StageImage->CreateRender(ImageName, _Order);
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
	StageImage->GetRender(0)->SetPosition(float4::Zero);
	StageImage->GetRender(0)->On();
}



//다음 Stage로 이동하는 함수
bool RoundLevelBase::MoveToNextStage()
{
	//이미 Stage가 이동중이라면 Return
	if (true == IsMoveValue)
		return false;

	//이번 스테이지가 마지막이였다면 처리하지 않음
	if (NowStageIndex + 1 == StageImage->GetRenderSize())
	{
		return true;
	}

	MonsterSpawners[NowStageIndex]->AllMonsterOff();

	//IsMoveValue이 true일때 Update에서 Stage가 이동함
	IsMoveValue = true;

	//다음 Stage의 렌더러 On
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	GameEngineRender* NextRender = StageImage->GetRender(NowStageIndex + 1);
	NextRender->On();
	NextRender->SetPosition(-ArrangeDir * ScreenSize);

	//이전 스테이지에 존재했던 Actor들을 삭제
	StageClear();

	return true;
}


void RoundLevelBase::StageClear()
{
	//스테이지 상의 버블 삭제
	std::vector<GameEngineActor*> Bubbles = GetActors(UpdateOrder::Player_Missle);
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		BubbleMissleFSM* BubbleFSM = dynamic_cast<BubbleMissle*>(Bubbles[i])->GetFSM();
		BubbleFSM->ChangeState(BubbleStateType::Pop);
	}

	//스테이지 상의 몬스터 투사체 삭제
	std::vector<GameEngineActor*> MonMissles = GetActors(UpdateOrder::Monster_Missle);
	for (GameEngineActor* MonMissle : MonMissles)
	{
		MonMissle->Death();
	}

	//스테이지 상의 특수버블 투사체 삭제
	std::vector<GameEngineActor*> NatureMissles = GetActors(UpdateOrder::Nature_Missle);
	for (GameEngineActor* NatureMissle : NatureMissles)
	{
		NatureMissle->Death();
	}

	//스테이지 상의 아이템 삭제
	std::vector<GameEngineActor*> Items = GetActors(UpdateOrder::Item);
	for (GameEngineActor* Item : Items)
	{
		Item->Death();
	}

	//스테이지 상의 포인트 이펙트 삭제
	std::vector<GameEngineActor*> Points = GetActors(UpdateOrder::PointEffect);
	for (GameEngineActor* Point : Points)
	{
		Point->Death();
	}

	//치트키를 이용시, 게임 다시 시작시 생기는 버그를 위한 작업
	std::vector<GameEngineActor*> BossArr = GetActors(UpdateOrder::BossMonster);
	for (GameEngineActor* Boss : BossArr)
	{
		Boss->Death();
	}
}







void RoundLevelBase::Update(float _DeltaTime)
{
	static float Timer = 0.f;
	const float StageChangeTime = 5.f;

	if ((nullptr != NextLevelDoor) && (true == NextLevelDoor->IsOpened()))
	{
		BubbleCore::GetInst().ChangeLevel("EndingLevel");
		return;
	}

	if (false ==IsMoveValue && true == MonsterSpawners[NowStageIndex]->IsAllMonsterOff())
	{
		Timer += _DeltaTime;
		if (Timer < StageChangeTime)
			return;


		//스테이지가 넘어갈 때 대기시간도 필요해 보임
		//if(false == );
		//	TODO

		if (NowStageIndex + 1 == StageImage->GetRenderSize())
		{
			//ChangeLastLevel();

			return;
		}

		//스테이지 이동이 시작
		Timer = 0.f;
		MoveToNextStage();
	}

	//IsMoving이 true일때만 Stage가 이동함
	if (false == IsMoveValue)
		return;

	//StageMoveDurationt 시간안에 Stage전환
	StageMoveTime += _DeltaTime;
	float Ratio = StageMoveTime / StageMoveDuration;

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//현재 스테이지
	{
		GameEngineRender* StageRender = StageImage->GetRender(NowStageIndex);
		float4 StartPos = float4::Zero;
		float4 DestPos = -ArrangeDir * ScreenSize;
		float4 NowPos = float4::LerpClamp(StartPos, DestPos, Ratio);
		StageRender->SetPosition(NowPos);
	}

	//다음 스테이지
	{
		GameEngineRender* StageRender = StageImage->GetRender(NowStageIndex + 1);
		float4 StartPos = ArrangeDir * ScreenSize;
		float4 DestPos = float4::Zero;
		float4 NowPos = float4::LerpClamp(StartPos, DestPos, Ratio);
		StageRender->SetPosition(NowPos);
	}

	//StageMoveDurationt을 경과했다면(스테이지 이동 끝)
	if (1.f < Ratio)
	{
		SetNowStage(NowStageIndex + 1);
		DestHelperPtr->TurnOnBubbleDest(NowStageIndex);
		IsMoveValue = false;
		StageMoveTime = 0.f;

		if (true == IsLastStage())
		{
			StartLastStage();
			BGMPlayer.PauseOn();
			BossBGMPlayer = GameEngineResources::GetInst().SoundPlayerToControl(BossBgmName);
			//얘 나중에 어디선가 꺼줘야해
		}
	}
}



//NowIndex가 현재 Round에서 마지막 Stage인지 알려주는 함수
bool RoundLevelBase::IsLastStage()
{
	return (NowStageIndex + 1) == StageImage->GetRenderSize();
}


//인자로 받는 _Pos가 레벨의 지형에 의해 막힌 곳인지 알려주는 함수
bool RoundLevelBase::IsBlockPos(const float4& _Pos)
{
	//현재 Stage에 맞게 Offset을 조정	(3번 스테이지라면 해상도.x * 3)
	float4 Offset = StageCollision->GetCutData(static_cast<int>(NowStageIndex)).GetStartPos();

	float4 DEbug = Offset + _Pos;

	//해당 지점의 색상 추출(스크린 밖으로도 나갈수 있는 상태)
	DWORD Color = StageCollision->GetPixelColor(Offset + _Pos, RGB(255, 255, 255));

	//검정색이라면 맵의 충돌체에 막혀있는곳
	return Color != RGB(255,255,255);
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
		Player = CreateActor<Player_Bubblun>(UpdateOrder::Player);
		break;
	case PlayerCharacterType::BOBBLUN:
		Player = CreateActor <Player_Bobblun>(UpdateOrder::Player);
		break;
	case PlayerCharacterType::KULULUN:
		Player = CreateActor <Player_Kululun>(UpdateOrder::Player);
		break;
	case PlayerCharacterType::CORORON:
		Player = CreateActor <Player_Cororon>(UpdateOrder::Player);
		break;
	}

}




void RoundLevelBase::BgmLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("BGM");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName(RoundBgmName));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName(BossBgmName));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName(ClearBgmName));
	IsLoad = true;
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

	//플레이어 위치 조정
	Player->SetPos(PlayerSpawnPos);
	DestHelperPtr->TurnOnBubbleDest(NowStageIndex);

	BGMPlayer = GameEngineResources::GetInst().SoundPlayerToControl(RoundBgmName);
	BGMPlayer.PauseOff();

	SetNowStage(0);
}

//레벨이 전환될때 레벨 정리하고 가기
void RoundLevelBase::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	IsMoveValue = false;
	//SetNowStage(0);
	Player->SetPos(PlayerSpawnPos);
	DestHelperPtr->TurnOnBubbleDest(NowStageIndex);

	BGMPlayer.Stop();

	StageClear();

	std::vector<GameEngineActor*> Bubbles = GetActors(UpdateOrder::Player_Missle);
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		Bubbles[i]->Death();
	}


	Bubbles.clear();

	if (nullptr != BossClearUI)
	{
		BossClearUI->Clear();
		BossClearUI->Death();
		BossClearUI = nullptr;
	}

	if (nullptr != NextLevelDoor)
	{
		NextLevelDoor->Death();
		NextLevelDoor = nullptr;
	}
}


//현재 Round의 Stage를 강제로 설정하는 함수
void RoundLevelBase::SetNowStage(size_t _StageNum)
{
	//모든 스테이지 끄기
	for (size_t i = 0; i < StageImage->GetRenderSize(); ++i)
	{
		StageImage->GetRender(i)->Off();
	}

	//인자로 받은_StageNum만 켜기
	NowStageIndex = _StageNum;
	StageImage->GetRender(NowStageIndex)->On();
	StageImage->GetRender(NowStageIndex)->SetPosition(float4::Zero);

	for (size_t i = 0; i < MonsterSpawners.size(); ++i)
	{
		MonsterSpawners[i]->AllMonsterOff();
	}

	MonsterSpawners[NowStageIndex]->AllMonsterOn();
}


std::vector<GameEngineActor*> RoundLevelBase::GetAliveMonsters()
{
	const std::vector<std::pair<GameEngineActor*, float4>>& Monsters = MonsterSpawners[NowStageIndex]->GetMonsters();

	std::vector<GameEngineActor*> StageMonsters;
	StageMonsters.reserve(Monsters.size());
	
	for (std::pair<GameEngineActor*, float4> Pair : Monsters)
	{
		//죽은 몬스터 또는 비 활성화 몬스터의 경우엔 Continue
		if (false == Pair.first->IsUpdate())
			continue;

		StageMonsters.push_back(Pair.first);
	}

	return StageMonsters;
}

void RoundLevelBase::StageBossClear()
{
	BossBGMPlayer.Stop();
	GameEngineResources::GetInst().SoundPlay(ClearBgmName);

	//나중에 어느 그룹에 넣을지 생각해보자, 아니면 씬이 전환될때 삭제하는 것도 방법이다
	CreateActor<BossDeadBox>(UpdateOrder::BossMonster);

	BossClearUI = CreateActor<BossDeadUI>();

	const float4 DoorPos = BubbleDestHelper::GetGridPos(635);
	NextLevelDoor = CreateActor<NextDoor>();
	NextLevelDoor->SetPos(DoorPos);
	NextLevelDoor->SelectDoor(DoorType::Gold, { 400.f, 400.f }, RenderOrder::Door);
}

