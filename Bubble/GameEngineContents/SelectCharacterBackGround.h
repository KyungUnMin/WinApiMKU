#pragma once
#include <GameEngineCore/GameEngineActor.h>


class SelectCharacterBackGround : public GameEngineActor
{
public:
	SelectCharacterBackGround();
	~SelectCharacterBackGround();

	SelectCharacterBackGround(const SelectCharacterBackGround& _Other) = delete;
	SelectCharacterBackGround(SelectCharacterBackGround&& _Other) noexcept = delete;
	SelectCharacterBackGround& operator=(const SelectCharacterBackGround& _Other) = delete;
	SelectCharacterBackGround& operator=(const SelectCharacterBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const float4	Offset[4];
	static const float	MoveSpeed;
	float4						ScreenSize = float4::Zero;
};

