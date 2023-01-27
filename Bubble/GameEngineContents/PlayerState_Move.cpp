#include "PlayerState_Move.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "RoundLevelBase.h"

PlayerState_Move::PlayerState_Move()
{

}

PlayerState_Move::~PlayerState_Move()
{

}

void PlayerState_Move::Start(PlayerCharacterType _CharacterType)
{
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerMove.bmp", 5, 4);
		ResourceLoad("Right_PlayerMove.bmp", 5, 4);
		IsLoad = true;
	}

	InitState("Move");

	int AniIndex = static_cast<int>(_CharacterType) * 5;

	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Move",
		.ImageName = "Left_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = 0.1f,
	});

	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Move",
		.ImageName = "Right_PlayerMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + 4,
		.InterTimer = 0.1f,
	});

	const std::string StartDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(StartDir + GetAniName());
	GetRender()->Off();



	RoundLevel = dynamic_cast<RoundLevelBase*>(GetPlayer()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel�� ���� ������ ����Ǿ� ���� �ʽ��ϴ�");
	}
}


void PlayerState_Move::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	float4 NowPos = GetPlayer()->GetPos();

	//���߿� �ִ� ���
	if (false == RoundLevel->IsBlockPos(NowPos + float4::Down))
	{
		GetOwner()->ChangeState(PlayerStateType::Falling);
		return;
	}

	//�����ϴ� ���
	if (true == GameEngineInput::IsDown(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//����Ű �� ���
	if (GameEngineInput::IsFree(PlayerLeft) && GameEngineInput::IsFree(PlayerRight))
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		return;
	}
	

	float4 MoveDir = GetPlayer()->GetDirVec();
	if (true == RoundLevel->IsBlockPos(NowPos + MoveDir * MovableActor::ColliderRange))
		return;

	GetPlayer()->SetMove(MoveDir * MoveSpeed * _DeltaTime);
}

