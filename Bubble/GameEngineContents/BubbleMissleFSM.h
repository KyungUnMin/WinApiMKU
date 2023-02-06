#pragma once
#include <vector>
#include "ContentsEnum.h"

enum class BubbleStateType
{
	Throw,
	Idle,
	/*Idle,
	Pop,
	Imminent,*/

	Count,
};

class BubbleMissleStateBase;
class BubbleMissle;

class BubbleMissleFSM
{
	friend BubbleMissle;

public:
	BubbleMissleFSM();
	~BubbleMissleFSM();

	BubbleMissleFSM(const BubbleMissleFSM& _Other) = delete;
	BubbleMissleFSM(BubbleMissleFSM&& _Other) noexcept = delete;
	BubbleMissleFSM& operator=(const BubbleMissleFSM& _Other) = delete;
	BubbleMissleFSM& operator=(const BubbleMissleFSM&& _Other) noexcept = delete;

	

	BubbleMissleStateBase* GetState(BubbleStateType _Type);

	void ChangeState(BubbleStateType _NextStateType)
	{
		ChangeState(GetState(_NextStateType));
	}
	void ChangeState(BubbleMissleStateBase* _NextState);

protected:

private:
	BubbleMissleStateBase*							CurState = nullptr;
	std::vector<BubbleMissleStateBase*>	States;
	BubbleMissle*											Bubble		= nullptr;

	void Init(PlayerCharacterType _CharType, BubbleMissleType _BubbleType);
	void Update(float _DeltaTime);

	//Ÿ�Կ� ���� ������Ʈ ����
	void CreateState(BubbleStateType _StateType);
};

