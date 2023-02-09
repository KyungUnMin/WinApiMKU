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
	PlayerFSM();
	~PlayerFSM();

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
	PlayerBase* Player = nullptr;
	PlayerStateBase* CurState = nullptr;
	std::vector<PlayerStateBase*>	States;

	//�ڷᱸ���� ��� FSM���� �����ϰ� ����
	void Start();

	//���� FSM ����
	void Update(float _DeltaTime);

	//Ÿ�Կ� ���� ������Ʈ ����
	void CreateState(PlayerStateType _StateType);
};

