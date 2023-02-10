#pragma once
#include <vector>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

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

class PlayerBase;
class PlayerStateBase;
class GameEngineRender;

//PlayerStateBase를 상속받은 클래스를 관리하는 FSM 클래스
class PlayerFSM
{
	friend PlayerBase;

public:
	PlayerFSM(const PlayerFSM& _Other) = delete;
	PlayerFSM(PlayerFSM&& _Other) noexcept = delete;
	PlayerFSM& operator=(const PlayerFSM& _Other) = delete;
	PlayerFSM& operator=(const PlayerFSM&& _Other) noexcept = delete;

	PlayerStateBase* GetState(PlayerStateType _Type);

	//FSM 변경(enum)
	void ChangeState(PlayerStateType _NextStateType)
	{
		ChangeState(GetState(_NextStateType));
	}

	//FSM 변경(PlayerStateBase 포인터)
	void ChangeState(PlayerStateBase* _NextState);

	inline GameEngineRender* GetRender()
	{
		return RenderPtr;
	}

protected:

private:
	std::vector<PlayerStateBase*>	States;
	PlayerBase*									Player						= nullptr;
	PlayerStateBase*						CurState					= nullptr;

	const float4								PlayerRenderScale	= float4{ 200.f, 200.f };
	GameEngineRender*					RenderPtr				= nullptr;

	PlayerFSM();
	~PlayerFSM();

	//자료구조에 모든 FSM들을 생성하고 관리
	void Start();

	//현재 FSM 동작
	void Update(float _DeltaTime);

	//타입에 따라 컴포넌트 생성
	void CreateState(PlayerStateType _StateType);
};

