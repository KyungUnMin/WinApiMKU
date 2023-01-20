#pragma once
#include <GameEngineCore/GameEngineActor.h>


class OpeningSpotLight : public GameEngineActor
{
public:
	OpeningSpotLight();
	~OpeningSpotLight();

	OpeningSpotLight(const OpeningSpotLight& _Other) = delete;
	OpeningSpotLight(OpeningSpotLight&& _Other) noexcept = delete;
	OpeningSpotLight& operator=(const OpeningSpotLight& _Other) = delete;
	OpeningSpotLight& operator=(const OpeningSpotLight&& _Other) noexcept = delete;

	inline void SetStopInfo(const float4& _StopPos, float _StopTime, float _OutTime)
	{
		StopPos = _StopPos;
		StopTime = _StopTime;
		OutTime = _OutTime;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float MoveSpeed = 500.f;

	float4		Dir				= { 1.f, -1.f };
	float4		StopPos		= float4::Zero;
	float		StopTime		= 300.f;
	float		OutTime		= 0.f;
};

