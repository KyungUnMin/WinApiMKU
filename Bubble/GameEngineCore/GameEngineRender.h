#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineObject.h"

class GameEngineActor;
class GameEngineLevel;

//주인(Owner)을 기준으로 이미지/애니메이션을 렌더링 해주는 객체, Level에서 관리함
class GameEngineRender : public GameEngineObject
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	GameEngineRender();
	~GameEngineRender();

	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(const GameEngineRender&& _Other) noexcept = delete;


	//GameEngineResources에서 이미지 찾아오기
	void SetImage(const std::string_view& _ImageName);


	//Offset 적용
	inline void SetPosition(const float4& _Position)
	{
		Position = _Position;
	}

	//크기 설정
	inline void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	//프레임 직접 지정
	void SetFrame(int _Frame);

	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	//Rendering되는 순서
	inline int GetOrder()
	{
		return Order;
	}

	inline int GetFrame()
	{
		return Frame;
	}

	inline float4 GetPosition()
	{
		return Position;
	}

	inline float4 GetScale()
	{
		return Scale;
	}
	

protected:

private:
	//이 객체를 가지고 있는 주인Actor
	GameEngineActor*		Owner			= nullptr;

	//렌더링 되는 순서
	int								Order			= 0;

	//Owner 기준 상대위치(오프셋)
	float4							Position		= float4::Zero;

	//이미지를 그릴 크기
	float4							Scale			= float4::Zero;

	//이미지 리소스와 연결된 GameEngineImage
	GameEngineImage*		Image			= nullptr;

	//이미지를 잘랐을때 그릴 이미지 인덱스
	int								Frame			= 0;



	//렌더링 되는 순서 결정 및 Level의 Renders에 등록(Actor에서만 호출)
	void SetOrder(int _Order);

	//Level의 Render를 통해 실제 렌더링되는 함수
	void Render(float _DeltaTime);
};

