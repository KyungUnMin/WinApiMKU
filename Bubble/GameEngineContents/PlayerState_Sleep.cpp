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
	bool AniLoop = true;
	if (_CharacterType == PlayerCharacterType::CORORON || _CharacterType == PlayerCharacterType::KULULUN)
	{
		AniLoop = false;
	}

	//�� State�� ���� �ʱ�ȭ
	PlayerStateBase::Init(
		"Left_PlayerSleep.bmp",
		"Right_PlayerSleep.bmp",
		"Sleep",
		std::make_pair(3, 4),
		0.25f, AniLoop);

	//�� �ѹ��� ���ҽ� �ε�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		PlayerStateBase::ResourceLoad();
		IsLoad = true;
	}

	//�ִϸ��̼� ���� �� RoundLevel�� ����
	PlayerStateBase::Start(_CharacterType);
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
	if (true == GameEngineInput::IsDown(PLAYER_JUMP))
	{
		GetOwner()->ChangeState(PlayerStateType::Jump);
		return;
	}

	//���� �Ǵ� ���������� �̵��Ϸ��� ������
	if (GameEngineInput::IsPress(PLAYER_RIGHT) || GameEngineInput::IsPress(PLAYER_LEFT))
	{
		GetOwner()->ChangeState(PlayerStateType::Move);
		return;
	}
}
