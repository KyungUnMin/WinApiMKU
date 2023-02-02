#pragma once
#include <vector>
#include <string>
#include <string_view>
#include "MovableActor.h"
#include "ContentsEnum.h"

enum class BubbleState
{
	Throw,
	Idle,
	Pop
};

class GameEngineRender;
class RoundLevelBase;
class GameEngineCollision;
class MonsterBase;

class BubbleMissleBase : public MovableActor
{
public:

	static const float				MoveSpeed;
	static const float				RaiseSpeed;	
	static const float4				RenderScale;
	static const float4				CollisionScale;

	BubbleMissleBase();
	~BubbleMissleBase() override;

	BubbleMissleBase(const BubbleMissleBase& _Other) = delete;
	BubbleMissleBase(BubbleMissleBase&& _Other) noexcept = delete;
	BubbleMissleBase& operator=(const BubbleMissleBase& _Other) = delete;
	BubbleMissleBase& operator=(const BubbleMissleBase&& _Other) noexcept = delete;

	//Throw �ִϸ��̼� ����
	virtual void CreateAnimation(PlayerCharacterType _CharacterType);

	inline BubbleState GetState()
	{
		return State;
	}

	virtual void BubblePop();

protected:
	//Throw �ִϸ��̼Ǹ� �����
	void Start() override;
	void Update(float _DeltaTime) final;

	//Throw�ִϸ��̼� �ε�
	void ResourceLoad(const std::string_view& _AniImgPath, int _X, int _Y);

	inline GameEngineRender* GetRender()
	{
		return BubbleRender;
	}

private:
	GameEngineRender*		BubbleRender	= nullptr;
	GameEngineCollision*		CollisionPtr		= nullptr;

	BubbleState						State				= BubbleState::Throw;
	RoundLevelBase*			RoundLevel		= nullptr;
	MonsterBase*					LockMonster	= nullptr;

	void ThrowUpdate(float _DeltaTime);
	void IdleUpdate(float _DeltaTime);
};

