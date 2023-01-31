#include "PlayerState_Sleep.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "RoundLevelBase.h"

PlayerState_Sleep::PlayerState_Sleep()
{

}

PlayerState_Sleep::~PlayerState_Sleep()
{

}

void PlayerState_Sleep::Start(PlayerCharacterType _CharacterType)
{
	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("Left_PlayerSleep.bmp", 3, 4);
		ResourceLoad("Right_PlayerSleep.bmp", 3, 4);
		IsLoad = true;
	}

	//���� Level�� ����
	PlayerStateBase::Start(_CharacterType);

	//�ִϸ��̼ǿ� Render ���� �� Renderũ�� ����
	SetAniRender("Sleep");

	//ĳ���� Ÿ��
	int AniIndex = static_cast<int>(_CharacterType) * 3;

	//ĳ���Ͱ� CORORON �̰ų� KULULUN�� ��쿣 �ִϸ��̼��� �ݺ�������� ����
	bool Repeat = true;
	if (_CharacterType == PlayerCharacterType::CORORON || 
		_CharacterType == PlayerCharacterType::KULULUN)
	{
		Repeat = false;
	}

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Left_Sleep",
		.ImageName = "Left_PlayerSleep.bmp",
		.Start = AniIndex,
		.End = AniIndex + 2,
		.InterTimer = 0.25f,
		.Loop = Repeat
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = "Right_Sleep",
		.ImageName = "Right_PlayerSleep.bmp",
		.Start = AniIndex,
		.End = AniIndex + 2,
		.InterTimer = 0.25f,
		.Loop = Repeat
	});

	//���� �޾ƿ���
	const std::string StartDir = GetPlayer()->GetDirStr();

	//���� ���⿡ ���� �ִϸ��̼� ��� ����
	GetRender()->ChangeAnimation(StartDir + GetAniName());

	//������ �� FSM���°� �ƴҼ� �ֱ� ������ ������ Off
	GetRender()->Off();
}

void PlayerState_Sleep::Update(float _DeltaTime)
{
	//�������� ��ȯ���϶�
	if (true == GetRoundLevel()->IsMoving())
	{
		GetOwner()->ChangeState(PlayerStateType::StageMove);
		return;
	}

	//����Ű�� ��������
	if (true == GameEngineInput::IsDown(PlayerJump))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//���� �Ǵ� ���������� �̵��Ϸ��� ������
	if (GameEngineInput::IsPress(PlayerRight) || GameEngineInput::IsPress(PlayerLeft))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}
}
