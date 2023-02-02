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

class BubbleMissleBase : public MovableActor
{
public:
	static const float				MoveSpeed;
	static const float				RaiseSpeed;	
	static const float4				RenderScale;

	BubbleMissleBase();
	~BubbleMissleBase() override;

	BubbleMissleBase(const BubbleMissleBase& _Other) = delete;
	BubbleMissleBase(BubbleMissleBase&& _Other) noexcept = delete;
	BubbleMissleBase& operator=(const BubbleMissleBase& _Other) = delete;
	BubbleMissleBase& operator=(const BubbleMissleBase&& _Other) noexcept = delete;

	//Throw 애니메이션 생성
	virtual void CreateAnimation(PlayerCharacterType _CharacterType);

protected:
	//Throw 애니메이션만 만든다
	void Start() override;
	void Update(float _DeltaTime) final;
	virtual void BubblePop() = 0;

	//Throw애니메이션 로드
	void ResourceLoad(const std::string_view& _AniImgPath, int _X, int _Y);

	inline GameEngineRender* GetRender()
	{
		return BubbleRender;
	}

private:
	GameEngineRender*		BubbleRender	= nullptr;
	BubbleState						State				= BubbleState::Throw;
	RoundLevelBase*			RoundLevel		= nullptr;

	void ThrowUpdate(float _DeltaTime);
	void IdleUpdate(float _DeltaTime);
};

