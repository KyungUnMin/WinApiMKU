#pragma once
#include <map>
#include <string.h>
#include <string_view>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineObject.h"

//CreateAnimation 함수의 인자가 될 구조체
class FrameAnimationParameter
{
public:
	//키값으로 사용할 애니메이션 이름
	std::string_view		AnimationName	= "";

	//불러올 이미지 이름
	std::string_view		ImageName			= "";


	//애니메이션 프레임이 순차적인 경우 
	//시작 프레임인덱스와 끝 프레임 인덱스를 지정
	int							Start					= 0;
	int							End						= 0;

	//시작할 인덱스
	//int						CurrentIndex		= 0;

	//애니메이션 프레임마다 출력 시간이 같은 경우 모든 프레임의 출력 시간 지정
	float						InterTimer			= 0.1f;

	bool							Loop					= true;

	//애니메이션 프레임이 순차적으로 출력되지 않는 경우 여기서 직접 지정해준다
	std::vector<int>		FrameIndex;
	//애니메이션 프레임마다 출력 시간이 다른 경우 여기서 직접 지정해준다
	std::vector<float>	FrameTime;
};

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
	
	//애니메이션 생성
	void CreateAnimation(const FrameAnimationParameter& _Parameter);

	//애니메이션 변환
	void ChangeAnimation(const std::string_view& _AnimationName);

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


	//애니메이션에 대한 정보는 밖에서는 필요하지 않다. 때문에 private
	//한장의 이미지에 대한 애니메이션 정보(단 잘려있는 이미지여야 함)
	class FrameAnimation
	{
	public:
		//이 애니메이션의 소유 렌더
		GameEngineRender*	Parent					= nullptr;
		GameEngineImage*		Image					= nullptr;

		//애니메이션을 그릴 잘린 이미지 인덱스
		std::vector<int>			FrameIndex;
		//해당 프레임마다 머무를 시간
		std::vector<float>		FrameTime;

		//현재 출력되고 있는 프레임 인덱스
		int								CurrentIndex		= 0;
		//현재 프레임이 다음 프레임으로 넘어가기까지 남아있는 시간
		float							CurrentTime		= 0.0f;
		//반복 여부
		bool								Loop					= true;


		//CurrentTime동안 FrameIndex[CurrentIndex]을 바탕으로 렌더링할 인덱스 결정
		void Render(float _DeltaTime);

		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

	std::map<std::string, FrameAnimation>	Animation;
	FrameAnimation*									CurrentAnimation = nullptr;
};

