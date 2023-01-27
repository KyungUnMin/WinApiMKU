#pragma once
#include <vector>
#include <string>
#include "ContentsEnum.h"
#include "ComponentBase.h"

enum class PlayerStateType
{
	Idle,
	Move,
	Falling,
	Jump,

	Count,
};

class PlayerStateBase;

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

	void ChangeState(PlayerStateType _NextStateType)
	{
		ChangeState(GetState(_NextStateType));
	}

	void ChangeState(PlayerStateBase* _NextState);

	void Init(PlayerCharacterType _CharacterType);
	void Update(float _DeltaTime) override;

protected:

private:
	PlayerStateBase*						CurState	= nullptr;
	std::vector<PlayerStateBase*>	States;

	void CreateState(PlayerStateType _StateType);
};

