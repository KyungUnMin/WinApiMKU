#pragma once

#include <list>
#include <string_view>

#include <Windows.h>

#include <GameEngineBase/GameEngineMath.h>

class GameEngineLevel;
class GameEngineRender;

class GameEngineActor
{
	friend GameEngineLevel;

public:
	GameEngineActor();
	~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;



	inline float4 GetPos()
	{
		return Pos;
	}

	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	inline GameEngineLevel* GetLevel()
	{
		return Level;
	}


	//내부에서  Enum을 int로 변환
#pragma region CreateRenderEnumOverLoadings

	template <typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	template <typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));
	}

#pragma endregion

	//CreateRender(int _Order)를 래핑 및 이미지 가져오기
	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);

	//GameEngineRender를 생성 및 연결하고 Level의 RenderList에 등록
	GameEngineRender* CreateRender(int _Order = 0);



protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

	//현재 Level이 시작되고 경과된 시간
	inline float GetLiveTime()
	{
		return LiveTime;
	}

private:
	GameEngineLevel*						Level			= nullptr;

	int												Order			= 0;
	float											LiveTime		= 0.0f;
	float4											Pos				= { 0.0f, 0.0f };
	std::list<GameEngineRender*>	RenderList;

	//GameEngineLevel만 호출 가능
	void SetOrder(int _Order)
	{
		Order = _Order;
	}
};

