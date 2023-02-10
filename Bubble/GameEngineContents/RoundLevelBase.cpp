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

const float RoundLevelBase::StageMoveDuration = 1.5f;

RoundLevelBase::RoundLevelBase()
{

}

RoundLevelBase::~RoundLevelBase()
{

}



void RoundLevelBase::Loading()
{
	DestHelperPtr = CreateActor<BubbleDestHelper>();
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

	//�̹� ���������� �������̿��ٸ� false�� ����
	if (NowStageIndex + 1 == StageImage->GetRenderSize())
	{
		return false;
	}


	//IsMoveValue�� true�϶� Update���� Stage�� �̵���
	IsMoveValue = true;

	//���� Stage�� ������ On
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	GameEngineRender* NextRender = StageImage->GetRender(NowStageIndex + 1);
	NextRender->On();
	NextRender->SetPosition(-ArrangeDir * ScreenSize);

	std::vector<GameEngineActor*> Bubbles = GetActors(UpdateOrder::Player_Missle);
	for (size_t i = 0; i < Bubbles.size(); ++i)
	{
		BubbleMissleFSM* BubbleFSM = dynamic_cast<BubbleMissle*>(Bubbles[i])->GetFSM();
		BubbleFSM->ChangeState(BubbleStateType::Pop);
	}

	return true;
}








void RoundLevelBase::Update(float _DeltaTime)
{
	if (nullptr != Player)
	{
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 PlayerPos = Player->GetPos();
		if (ScreenSize.y + 100.f < PlayerPos.y)
		{
			Player->SetMove(float4::Up * ScreenSize.y);
		}
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

	//StageMoveDurationt�� ����ߴٸ�
	if (1.f < Ratio)
	{
		SetNowStage(NowStageIndex + 1);
		DestHelperPtr->TurnOnBubbleDest(NowStageIndex);
		IsMoveValue = false;
		StageMoveTime = 0.f;
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

	if (true == PlayerSpwanPos.empty())
	{
		size_t Index = ImageName.find('_', 0);
		MsgAssert(ImageName.substr(0, Index) + " ������ �÷��̾� ���� ��ġ�� ���������� �ʾҽ��ϴ�");
	}

	//�÷��̾� ��ġ ����
	Player->SetPos(PlayerSpwanPos[0]);
	DestHelperPtr->TurnOnBubbleDest(NowStageIndex);
}

//������ ��ȯ�ɶ� ���� �����ϰ� ����
void RoundLevelBase::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	IsMoveValue = false;
	SetNowStage(0);
	Player->SetPos(PlayerSpwanPos[0]);
	DestHelperPtr->TurnOnBubbleDest(NowStageIndex);
}

const float4& RoundLevelBase::GetPlayerSpawnPos()
{
	if (PlayerSpwanPos.size() <= NowStageIndex)
	{
		MsgAssert("�ش� Stage���� �÷��̾� ���� ��ġ�� ���������� �ʾҽ��ϴ�");
		return float4::Zero;
	}

	return PlayerSpwanPos[NowStageIndex];
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
}

