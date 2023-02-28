#pragma once
#include "MonsterBase.h"


enum class Titama_AniType
{
	Right_ReflectionFly,
	Left_ReflectionFly,
	Right_ReflectionFly_Rage,
	Left_ReflectionFly_Rage,

	Lock,
	Lock_Rage,
	Dead,

	Count
};

class FrameAnimationParameter;

class Monster_Titama : public MonsterBase
{
public:
	friend class Titama_AniParamInit;

	static const std::string_view		RightImagePath;
	static const std::string_view		LeftImagePath;
	static const std::string_view		RightRageImagePath;
	static const std::string_view		LeftRageImagePath;
	static const std::string_view		LockImagePath;
	static const std::string_view		DeadImagePath;

	Monster_Titama();
	~Monster_Titama();

	Monster_Titama(const Monster_Titama& _Other) = delete;
	Monster_Titama(Monster_Titama&& _Other) noexcept = delete;
	Monster_Titama& operator=(const Monster_Titama& _Other) = delete;
	Monster_Titama& operator=(const Monster_Titama&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override
	{
		IsAlreadyFall = false;
	}

private:
	bool IsAlreadyFall = false;

	void ResourceLoad();
	bool FallingToFly(float _DeltaTime);

	static std::vector<FrameAnimationParameter> AniParams;
};

