#include "NextDoor.h"
#include <vector>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "RoundLevelBase.h"
#include "PlayerBase.h"
#include "PlayerState.h"

const float4 NextDoor::CollisionScale = {8.f, 8.f};
const float4 NextDoor::CollisionOffset = { 0.f, 20.f };

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

	//�浹ü ����
	CollisionPtr = CreateCollision(CollisionOrder::Door);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);
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

	//�÷��̾�� �浹ó��
	CollisionPlayer();

	//�ִϸ��̼� ó��
	DoorAnimation();
}


void NextDoor::CollisionPlayer()
{
	//�̹� �÷��̾�� �����ٸ�
	if (true == IsPlayerCollision)
		return;

	//�÷��̾�� �� ���� �� vs �� �浹��������
	std::vector<GameEngineCollision*> Players;
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }, Players))
		return;

	for (size_t i = 0; i < Players.size(); ++i)
	{
		PlayerBase* Player = dynamic_cast<PlayerBase*>(Players[i]->GetActor());
		PlayerState* PlayerFSM = Player->GetComponent<PlayerState>(ComponentType::PlayerState);
		PlayerFSM->ChangeState(PlayerStateType::EnterDoor);
	}

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

//�ʱ� ���·� �ǵ�����
void NextDoor::Reset()
{
	DoorRender->ChangeAnimation("Create", true);
	IsOpenedValue = false;
	IsPlayerCollision = false;
}

