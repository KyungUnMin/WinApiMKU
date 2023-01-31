#pragma once
#include <vector>
#include <string>
#include "ContentsEnum.h"
#include "ComponentBase.h"

//�÷��̾� ������ ����
enum class PlayerStateType
{
	Idle,
	Move,
	Falling,
	Jump,
	StageMove,
	Sleep,
	Damaged,

	Count,
};

class PlayerStateBase;

//PlayerStateBase�� ��ӹ��� Ŭ������ �����ϴ� FSM Ŭ����
class PlayerState : public ComponentBase
{
public:
	PlayerState();
	~PlayerState() override;

	PlayerState(const PlayerState& _Other) = delete;
	PlayerState(PlayerState&& _Other) noexcept = delete;
	PlayerState& operator=(const PlayerState& _Other) = delete;
	PlayerState& operator=(const PlayerState&& _Other) noexcept = delete;

	PlayerStateBase* GetState(PlayerStateType _Type);

	//FSM ����(enum)
	void ChangeState(PlayerStateType _NextStateType)
	{
		ChangeState(GetState(_NextStateType));
	}

	//FSM ����(PlayerStateBase ������)
	void ChangeState(PlayerStateBase* _NextState);

	//(PlayerBase�� ��ӹ��� ��ü���� ���� ȣ��)
	//�ڷᱸ���� ��� FSM���� �����ϰ� ����
	void Init(PlayerCharacterType _CharacterType);

	//���� FSM ����
	void Update(float _DeltaTime) override;

protected:

private:
	PlayerStateBase*						CurState	= nullptr;
	std::vector<PlayerStateBase*>	States;

	//Ÿ�Կ� ���� ������Ʈ ����
	void CreateState(PlayerStateType _StateType);
};

