#include "PlayerState_StageMove.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"
#include "PlayerBase.h"
#include "PlayerState.h"
#include "Gravity.h"

PlayerState_StageMove::PlayerState_StageMove()
{

}

PlayerState_StageMove::~PlayerState_StageMove()
{

}

void PlayerState_StageMove::Start(PlayerCharacterType _CharacterType)
{
	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerStageMove.bmp",
		"Right_PlayerStageMove.bmp",
		"StageMove",
		std::make_pair(3, 4));

	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		ResourceLoad("StageMoveBubble.bmp", std::make_pair(3,1));
		IsLoad = true;
	}

	//�ִϸ��̼� ���� �� RoundLevel�� ����
	PlayerStateBase::Start(_CharacterType);

	//���� ���� ��ǰ �ִϸ��̼� ����(private)
	CreateBubbleAni();
}

void PlayerState_StageMove::CreateBubbleAni()
{
	//�÷��̾ Render��ü ������ �� �޾ƿ���
	ClearBubble = GetPlayer()->CreateRender(RenderOrder::ClearBubble);

	//�ִϸ��̼� ����
	ClearBubble->CreateAnimation
	({
		.AnimationName = "ClearBubble",
		.ImageName = "StageMoveBubble.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.1f,
	});

	//ũ�� ����
	ClearBubble->SetScale({ 200.f, 200.f });
	//�ִϸ��̼� ��� ����
	ClearBubble->ChangeAnimation("ClearBubble");
	//������ �� FSM���°� �ƴҼ� �ֱ� ������ ������ Off
	ClearBubble->Off();
	//��ġ�� ����
	ClearBubble->SetPosition(float4::Up * 30.f);
}



//�÷��̾� �ִϸ��̼� �ѱ� & ���� ��ǰ �ѱ�
void PlayerState_StageMove::EnterState()
{
	//Stage�� ��ȯ�ɶ� ó�� �÷��̾� ��ġ ���
	PlayerOriginPos = GetPlayer()->GetPos();

	GetRender()->On();
	ClearBubble->On();
	Gravity::GlobalGravityUse = false;
}

void PlayerState_StageMove::Update(float _DeltaTime)
{
	//���� ������ Stage�� ��ȯ���̶�� �÷��̾ �̵���Ų��
	if (true == GetRoundLevel()->IsMoving())
	{
		float StageMoveTime = GetRoundLevel()->GetStageMoveTime();
		float Ratio = StageMoveTime / RoundLevelBase::StageMoveDuration;

		float4 DestPos = GetRoundLevel()->GetPlayerSpawnPos();
		float4 NextPos = float4::LerpClamp(PlayerOriginPos, DestPos, Ratio);
		GetPlayer()->SetPos(NextPos);
		return;
	}
	
	//���� ������ Stage ��ȯ�� �����ٸ� Idle���·� ��ȯ
	GetOwner()->ChangeState(PlayerStateType::Idle);
}

//�÷��̾� �ִϸ��̼� ���� & ���� ��ǰ ����
void PlayerState_StageMove::ExitState()
{
	GetRender()->Off();
	ClearBubble->Off();
	Gravity::GlobalGravityUse = true;
}

