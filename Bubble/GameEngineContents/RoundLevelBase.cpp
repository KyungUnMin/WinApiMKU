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




//������ ������ �浹ü�� �ε��ϴ� �Լ�
void RoundLevelBase::LoadStage(const std::string_view& _RoundName, int _X, int _Y)
{
	//��� RoundLevel�� Obstacle�� �� ������ ����Ǿ� �ִ�
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("Stage");

	//���� �浹ü Load
	//"Round" + _RoundName + "_Collider.bmp"
	ImageName += _RoundName.data();


	StageCollision = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName + "_Collider.bmp"));
	StageCollision->Cut(_X, _Y);

	//���� ���� �̹��� �ε�
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

//������ ������ �����ϴ� �Լ�
void RoundLevelBase::CreateStage(const float4& _ArrangeDir, int _Order)
{
	//���� ������ ���α�
	for (size_t i = 0; i < StageImage->GetRenderCapacity(); ++i)
	{
		GameEngineRender* Render = StageImage->CreateRender(ImageName, _Order);
		Render->SetFrame(static_cast<int>(i));
		Render->Off();
	}

	if ((_ArrangeDir != float4::Right) && (_ArrangeDir != float4::Down))
	{
		MsgAssert("float4::Right �Ǵ� float4::Down �������θ� ������ ������ �� �ֽ��ϴ�.");
		return;
	}

	ArrangeDir = _ArrangeDir;

	//ù��° �������� ȭ�� �� �߾ӿ� ����
	StageImage->GetRender(0)->SetPosition(float4::Zero);
	StageImage->GetRender(0)->On();
}



//���� Stage�� �̵��ϴ� �Լ�
bool RoundLevelBase::MoveToNextStage()
{
	//�̹� Stage�� �̵����̶�� Return
	if (true == IsMoveValue)
		return false;

	//�̹� ���������� �������̿��ٸ� ó������ ����
	if (NowStageIndex + 1 == StageImage->GetRenderSize())
	{
		return true;
	}

	MonsterSpawners[NowStageIndex]->AllMonsterOff();

	//IsMoveValue�� true�϶� Update���� Stage�� �̵���
	IsMoveValue = true;

	//���� Stage�� ������ On
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	GameEngineRender* NextRender = StageImage->GetRender(NowStageIndex + 1);
	NextRender->On();
	NextRender->SetPosition(-ArrangeDir * ScreenSize);

	//���� ���������� �����ߴ� Actor���� ����
	StageClear();

	return true;
}


void RoundLevelBase::StageClear()
{
	//�������� ���� ���� ����
	std::vector<GameEngineActor*> Bubbles = GetActors(UpdateOrder::Player_Missle);
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		BubbleMissleFSM* BubbleFSM = dynamic_cast<BubbleMissle*>(Bubbles[i])->GetFSM();
		BubbleFSM->ChangeState(BubbleStateType::Pop);
	}

	//�������� ���� ���� ����ü ����
	std::vector<GameEngineActor*> MonMissles = GetActors(UpdateOrder::Monster_Missle);
	for (GameEngineActor* MonMissle : MonMissles)
	{
		MonMissle->Death();
	}

	//�������� ���� Ư������ ����ü ����
	std::vector<GameEngineActor*> NatureMissles = GetActors(UpdateOrder::Nature_Missle);
	for (GameEngineActor* NatureMissle : NatureMissles)
	{
		NatureMissle->Death();
	}

	//�������� ���� ������ ����
	std::vector<GameEngineActor*> Items = GetActors(UpdateOrder::Item);
	for (GameEngineActor* Item : Items)
	{
		Item->Death();
	}

	//�������� ���� ����Ʈ ����Ʈ ����
	std::vector<GameEngineActor*> Points = GetActors(UpdateOrder::PointEffect);
	for (GameEngineActor* Point : Points)
	{
		Point->Death();
	}

	//ġƮŰ�� �̿��, ���� �ٽ� ���۽� ����� ���׸� ���� �۾�
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


		//���������� �Ѿ �� ���ð��� �ʿ��� ����
		//if(false == );
		//	TODO

		if (NowStageIndex + 1 == StageImage->GetRenderSize())
		{
			//ChangeLastLevel();

			return;
		}

		//�������� �̵��� ����
		Timer = 0.f;
		MoveToNextStage();
	}

	//IsMoving�� true�϶��� Stage�� �̵���
	if (false == IsMoveValue)
		return;

	//StageMoveDurationt �ð��ȿ� Stage��ȯ
	StageMoveTime += _DeltaTime;
	float Ratio = StageMoveTime / StageMoveDuration;

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//���� ��������
	{
		GameEngineRender* StageRender = StageImage->GetRender(NowStageIndex);
		float4 StartPos = float4::Zero;
		float4 DestPos = -ArrangeDir * ScreenSize;
		float4 NowPos = float4::LerpClamp(StartPos, DestPos, Ratio);
		StageRender->SetPosition(NowPos);
	}

	//���� ��������
	{
		GameEngineRender* StageRender = StageImage->GetRender(NowStageIndex + 1);
		float4 StartPos = ArrangeDir * ScreenSize;
		float4 DestPos = float4::Zero;
		float4 NowPos = float4::LerpClamp(StartPos, DestPos, Ratio);
		StageRender->SetPosition(NowPos);
	}

	//StageMoveDurationt�� ����ߴٸ�(�������� �̵� ��)
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
			//�� ���߿� ��𼱰� �������
		}
	}
}



//NowIndex�� ���� Round���� ������ Stage���� �˷��ִ� �Լ�
bool RoundLevelBase::IsLastStage()
{
	return (NowStageIndex + 1) == StageImage->GetRenderSize();
}


//���ڷ� �޴� _Pos�� ������ ������ ���� ���� ������ �˷��ִ� �Լ�
bool RoundLevelBase::IsBlockPos(const float4& _Pos)
{
	//���� Stage�� �°� Offset�� ����	(3�� ����������� �ػ�.x * 3)
	float4 Offset = StageCollision->GetCutData(static_cast<int>(NowStageIndex)).GetStartPos();

	float4 DEbug = Offset + _Pos;

	//�ش� ������ ���� ����(��ũ�� �����ε� ������ �ִ� ����)
	DWORD Color = StageCollision->GetPixelColor(Offset + _Pos, RGB(255, 255, 255));

	//�������̶�� ���� �浹ü�� �����ִ°�
	return Color != RGB(255,255,255);
}


//PlayerCharacterType Ÿ�Կ� ���� �÷��̾ �����ϴ� �Լ�
void RoundLevelBase::CreatePlayer(PlayerCharacterType _Type)
{
	SelectedCharacter = _Type;

	//�̹� �� �÷��̾ �����Ѵٸ�(ReStart �� ��� �̹� ������ ���� ����)
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

	//���������� Round������ �ƴѰ��
	if (nullptr == PrevRoundLevel)
	{
		//�⺻ ĳ����(�ʷϻ�) ����
		CreatePlayer(SelectedCharacter);
	}

	//���������� Round������ ��� ������ �÷��̾� Ÿ�Կ� ���� �� �÷��̾� ����
	else
	{
		CreatePlayer(PrevRoundLevel->GetSelectCharacter());
	}

	//�÷��̾� ��ġ ����
	Player->SetPos(PlayerSpawnPos);
	DestHelperPtr->TurnOnBubbleDest(NowStageIndex);

	BGMPlayer = GameEngineResources::GetInst().SoundPlayerToControl(RoundBgmName);
	BGMPlayer.PauseOff();

	SetNowStage(0);
}

//������ ��ȯ�ɶ� ���� �����ϰ� ����
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


//���� Round�� Stage�� ������ �����ϴ� �Լ�
void RoundLevelBase::SetNowStage(size_t _StageNum)
{
	//��� �������� ����
	for (size_t i = 0; i < StageImage->GetRenderSize(); ++i)
	{
		StageImage->GetRender(i)->Off();
	}

	//���ڷ� ����_StageNum�� �ѱ�
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
		//���� ���� �Ǵ� �� Ȱ��ȭ ������ ��쿣 Continue
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

	//���߿� ��� �׷쿡 ������ �����غ���, �ƴϸ� ���� ��ȯ�ɶ� �����ϴ� �͵� ����̴�
	CreateActor<BossDeadBox>(UpdateOrder::BossMonster);

	BossClearUI = CreateActor<BossDeadUI>();

	const float4 DoorPos = BubbleDestHelper::GetGridPos(635);
	NextLevelDoor = CreateActor<NextDoor>();
	NextLevelDoor->SetPos(DoorPos);
	NextLevelDoor->SelectDoor(DoorType::Gold, { 400.f, 400.f }, RenderOrder::Door);
}

