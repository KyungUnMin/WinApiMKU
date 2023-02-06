#pragma once
#include <vector>
#include <string>
#include "ContentsEnum.h"
#include "ComponentBase.h"

//플레이어 상태의 종류
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

class PlayerStateBase;

//PlayerStateBase를 상속받은 클래스를 관리하는 FSM 클래스
class PlayerState : public ComponentBase
{
public:
	PlayerState();
	~PlayerState() override;

	PlayerState(const PlayerState& _Other) = delete;
	PlayerState(PlayerState&& _Other) noexcept = delete;
	PlayerState& operator=(const PlayerState& _Other) = delete;
	PlayerState& operator=(const PlayerState&& _Other) noexcept = delete;


	//자료구조에 모든 FSM들을 생성하고 관리
	void Start() override;

	//현재 FSM 동작
	void Update(float _DeltaTime) override;

	PlayerStateBase* GetState(PlayerStateType _Type);

	//FSM 변경(enum)
	void ChangeState(PlayerStateType _NextStateType)
	{
		ChangeState(GetState(_NextStateType));
	}

	//FSM 변경(PlayerStateBase 포인터)
	void ChangeState(PlayerStateBase* _NextState);


protected:

private:
	PlayerStateBase*						CurState	= nullptr;
	std::vector<PlayerStateBase*>	States;

	//타입에 따라 컴포넌트 생성
	void CreateState(PlayerStateType _StateType);
};

