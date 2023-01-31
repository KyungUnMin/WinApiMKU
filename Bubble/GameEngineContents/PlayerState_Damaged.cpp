#include "PlayerState_Damaged.h"
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "PlayerState.h"

PlayerState_Damaged::PlayerState_Damaged()
{

}

PlayerState_Damaged::~PlayerState_Damaged()
{

}

void PlayerState_Damaged::Start(PlayerCharacterType _CharacterType)
{
	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerDamaged.bmp", ImgColCnt, 4);
		ResourceLoad("Right_PlayerDamaged.bmp", ImgColCnt, 4);
		IsLoad = true;
	}

	
	
	//���� Level�� ����
	PlayerStateBase::Start(_CharacterType);

	//�ִϸ��̼ǿ� Render ���� �� �̸� ����(���⼭ Renderũ�⵵ ����)
	SetAniRender("Damaged");



	//ĳ���� Ÿ��
	int AniIndex = static_cast<int>(_CharacterType) * ImgColCnt;

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Damaged",
		.ImageName = "Left_PlayerDamaged.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgColCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Damaged",
		.ImageName = "Right_PlayerDamaged.bmp",
		.Start = AniIndex,
		.End = AniIndex + ImgColCnt - 1,
		.InterTimer = 0.1f,
		.Loop = false
	});

	//���� �޾ƿ���
	const std::string StartDir = GetPlayer()->GetDirStr();

	//���� ���⿡ ���� �ִϸ��̼� ��� ����
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//������ �� FSM���°� �ƴҼ� �ֱ� ������ ������ Off
	GetRender()->Off();
}

void PlayerState_Damaged::Update(float _DeltaTime)
{
	//�ִϸ��̼��� ���������� ���
	if (false == GetRender()->IsAnimationEnd())
		return;

	

	//�÷��̾� ������� ���ҽ�Ű�� �÷��̾ ����ִٸ�
	if (true == GetPlayer()->DecreaseLife())
	{
		GetOwner()->ChangeState(PlayerStateType::Idle);
		//GetPlayer()->SetPos(GetRoundLevel()->)
		return;
	}

	//�÷��̾ �׾�����
	GetPlayer()->Death();

	//TODO
	//GetRoundLevel()->
}

void PlayerState_Damaged::EnterState()
{
	const std::string StartDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(StartDir + GetAniName(), true);
	GetRender()->On();
}

