#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class EnterRoundCharater : public GameEngineActor
{
public:
	//인자로 받은 캐릭터 타입에 따른 애니메이션 생성 및 재생
	void SetCharacter(int _CharacterIndex);

	EnterRoundCharater();
	~EnterRoundCharater();

	EnterRoundCharater(const EnterRoundCharater& _Other) = delete;
	EnterRoundCharater(EnterRoundCharater&& _Other) noexcept = delete;
	EnterRoundCharater& operator=(const EnterRoundCharater& _Other) = delete;
	EnterRoundCharater& operator=(const EnterRoundCharater&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//현재 각도
	float				Radian			= 0.f;

	//1초당 각도 증가률(라디안)
	const float		AddRadian	= 1.f;

	//반지름
	float				Radius			= 100.f;

	GameEngineRender* PlayerRender = nullptr;
	GameEngineRender* BubbleRender = nullptr;
};

