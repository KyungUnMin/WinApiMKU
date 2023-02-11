#include "PlayerState_StageMove.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "RoundLevelBase.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"
#include "Gravity.h"

PlayerState_StageMove::PlayerState_StageMove()
{

}

PlayerState_StageMove::~PlayerState_StageMove()
{

}

void PlayerState_StageMove::Start(PlayerCharacterType _CharacterType)
{
	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad();
		IsLoad = true;
	}

	ConnectRoundLevel();
	CreateAnimation(_CharacterType);

	//���� ���� ��ǰ �ִϸ��̼� ����(private)
	CreateBubbleAni();
}


void PlayerState_StageMove::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	Dir.Move("StageMove");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Left_PlayerStageMove.bmp"))->Cut(3, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Right_PlayerStageMove.bmp"))->Cut(3, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StageMoveBubble.bmp"))->Cut(3, 1);
}

void PlayerState_StageMove::CreateAnimation(PlayerCharacterType _CharacterType)
{
	int ImgXCnt = 3;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	SetAniName("StageMove");
	std::string LeftAniName = MovableActor::LeftStr + GetAniName();
	std::string RightAniName = MovableActor::RightStr + GetAniName();

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = "Left_PlayerStageMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = "Right_PlayerStageMove.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = 0.1f,
	});
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
	PlayerStateBase::EnterState();

	//Stage�� ��ȯ�ɶ� ó�� �÷��̾� ��ġ ���
	PlayerOriginPos = GetPlayer()->GetPos();
	ClearBubble->On();
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
	GetFSM()->ChangeState(PlayerStateType::Idle);
}

//�÷��̾� �ִϸ��̼� ���� & ���� ��ǰ ����
void PlayerState_StageMove::ExitState()
{
	ClearBubble->Off();
}

