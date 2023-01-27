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

	//n초 시간이 흐른후 고정 위치, n초 시간, 밖으로 빠져 나갈수 있는 시간
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

	//현재 스포트 라이트의 방향
	float4		Dir				= { 1.f, -1.f };

	//n초 시간이 흐른후 고정 위치
	float4		StopPos		= float4::Zero;

	//n초
	float		StopTime		= 300.f;

	//밖으로 빠져 나갈수 있는 시간
	float		OutTime		= 0.f;
};

