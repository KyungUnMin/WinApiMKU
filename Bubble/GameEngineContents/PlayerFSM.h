#pragma once
#include <vector>
#include <string>
#include "ContentsEnum.h"

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
	EnterDoor,

	Count,
};

class PlayerBase;
class PlayerStateBase;

//PlayerStateBase�� ��ӹ��� Ŭ������ �����ϴ� FSM Ŭ����
class PlayerFSM
{
	friend PlayerBase;

public:
	PlayerFSM(const PlayerFSM& _Other) = delete;
	PlayerFSM(PlayerFSM&& _Other) noexcept = delete;
	PlayerFSM& operator=(const PlayerFSM& _Other) = delete;
	PlayerFSM& operator=(const PlayerFSM&& _Other) noexcept = delete;

	PlayerStateBase* GetState(PlayerStateType _Type);

	//FSM ����(enum)
	void ChangeState(PlayerStateType _NextStateType)
	{
		ChangeState(GetState(_NextStateType));
	}

	//FSM ����(PlayerStateBase ������)
	void ChangeState(PlayerStateBase* _NextState);


protected:

private:
	std::vector<PlayerStateBase*>	States;
	PlayerBase*									Player			= nullptr;
	PlayerStateBase*						CurState		= nullptr;

	PlayerFSM();
	~PlayerFSM();

	//�ڷᱸ���� ��� FSM���� �����ϰ� ����
	void Start();

	//���� FSM ����
	void Update(float _DeltaTime);

	//Ÿ�Կ� ���� ������Ʈ ����
	void CreateState(PlayerStateType _StateType);
};

