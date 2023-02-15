#include "NextDoor.h"
#include <vector>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "RoundLevelBase.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"


NextDoor::NextDoor()
{

}

NextDoor::~NextDoor()
{

}


void NextDoor::Start()
{
	//�� Ŭ���� ��Ʋ�� ó������ ���ҽ� �ε��ϱ�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}
}


//�� Ŭ���� ���ʷ� ���ҽ� �޾ƿ���
void NextDoor::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NextDoor.bmp"))->Cut(5, 9);
}


void NextDoor::SetScale(float4 _Scale)
{
	//����ó��
	if (nullptr == DoorRender)
	{
		MsgAssert("Door�� ������ ���������� �ʾҽ��ϴ�");
		return;
	}

	DoorRender->SetScale(_Scale);
}


//���� ������ ���� �ִϸ��̼� ����
void NextDoor::CreateDoorAni(DoorType _DoorType)
{
	//����ó��
	if (nullptr == DoorRender)
	{
		MsgAssert("Door�� ������ ���������� �ʾҽ��ϴ�");
		return;
	}

	//�� ���� �ִϸ��̼�
	DoorRender->CreateAnimation
	({
		.AnimationName = "Create",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_DoorType),
		.End = static_cast<int>(_DoorType) + 6,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//�� ���� �ִϸ��̼�
	DoorRender->CreateAnimation
	({
		.AnimationName = "Open",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_DoorType) + 6,
		.End = static_cast<int>(_DoorType) + 10,
		.InterTimer = 0.1f,
	});

	//���� ������ ��ٸ��� �ִϸ��̼�
	DoorRender->CreateAnimation
	({
		.AnimationName = "Wait",
		.ImageName = "NextDoor.bmp",
		.Start = static_cast<int>(_DoorType) + 10,
		.End = static_cast<int>(_DoorType) + 13,
		.InterTimer = 0.1f,
	});

	//ó���� �� ���� �ִϸ��̼����� ����
	DoorRender->ChangeAnimation("Create");
}



void NextDoor::Update(float _DeltaTime)
{
	//����ó��
	if (nullptr == DoorRender)
	{
		MsgAssert("Door�� ������ ���������� �ʾҽ��ϴ�");
		return;
	}

	CreateLiveTime += _DeltaTime;

	//�÷��̾�� �浹ó��
	CollisionPlayer();

	//�ִϸ��̼� ó��
	DoorAnimation();

	//�÷��̾�� �浹������ �÷��̾� ��ġ�� �ڽ��� ��ġ�� �̵�
	MovePlayer();
}


void NextDoor::CollisionPlayer()
{
	//�̹� �÷��̾�� �����ٸ�
	if (true == IsPlayerCollision)
		return;

	if (CreateLiveTime < CollisionOkTime)
		return;


	//�÷��̾�� �� ���� �� vs �� �浹��������
	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 PlayerCollisionScale = PlayerBase::MainPlayer->CollisionScale;
	if (false == GameEngineCollision::CollisionCircleToPoint({ PlayerPos , PlayerCollisionScale }, { GetPos(), float4::Zero }))
		return;

	PlayerFSM* Fsm = PlayerBase::MainPlayer->GetFSM();
	Fsm->ChangeState(PlayerStateType::EnterDoor);
	PlayerColPos = PlayerPos;
	ColisionTime = CreateLiveTime;

	DoorOpen();
	IsPlayerCollision = true;
}

void NextDoor::DoorAnimation()
{
	//���� �̹� �� ���� ���¶�� return
	if (true == IsOpenedValue)
		return;

	//������� �Դٸ� ���� �����ְų� ������ ��

	//���� �� ���������� ����  (10, 24, 38 �������϶��� return �Ʒ� �ڵ带 ����)
	//���� ���� ���´� Frame�� 10, 24, 38�� ������ ���� ���� ������ �ڵ����� return�ȴ�
	int Frame = DoorRender->GetFrame();
	if ((Frame - 10) % 14)
		return;

	//���� �� ���� ����

	//���� �ִϸ��̼�(���� ���� ������ ��ٸ��� �ִ� �ִϸ��̼�)���� �̵�
	IsOpenedValue = true;
	DoorRender->ChangeAnimation("Wait");
}



void NextDoor::DoorOpen()
{
	if (true == IsOpenedValue)
		return;

	/*
	* ChangeAnimation���ο��� ���� �ִϸ��̼� ���� �̵��� ��������
	* �׷��� Open�ִϸ��̼� �϶� �� �Լ��� ������ ȣ��ǵ� �������
	*/
	DoorRender->ChangeAnimation("Open");
}


void NextDoor::MovePlayer()
{
	if (false == IsPlayerCollision)
		return;

	//�÷��̾�� �浹�� �� �帥 �ð�
	float NowDuration = CreateLiveTime - ColisionTime;

	float Ratio = NowDuration / MoveDuration;

	float4 PlayerMovePos = float4::LerpClamp(PlayerColPos, GetPos(), Ratio);

	PlayerBase::MainPlayer->SetPos(PlayerMovePos);
}

//�ʱ� ���·� �ǵ�����
void NextDoor::Reset()
{
	DoorRender->ChangeAnimation("Create", true);
	IsOpenedValue = false;
	IsPlayerCollision = false;
	CreateLiveTime = 0.f;
	ColisionTime = 0.f;
}

