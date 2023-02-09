#pragma once
#include <map>
#include <string.h>
#include <string_view>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineComponent.h"

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
class GameEngineRender : public GameEngineComponent
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

	//이미지 설정하고 크기도 리소스의 이미지크기로 설정
	void SetImageToScaleToImage(const std::string_view& _ImageName);

	//렌더링 이미지를 실제 리소스의 이미지 크기로 설정
	void SetScaleToImage();


	//프레임 직접 지정
	void SetFrame(int _Frame);


	inline GameEngineImage* GetImage()
	{
		return Image;
	}

	inline int GetFrame()
	{
		return Frame;
	}


	//TransparentBlt할때 지울 배경색상값 변경
	inline void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	//카메라 영향 받는지 여부 설정
	inline void SetEffectCamera(bool _Effect)
	{
		IsEffectCamera = _Effect;
	}

	
	//카메라 영향 끄기
	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}

	//카메라 영향 켜기
	inline void EffectCameraOn()
	{
		SetEffectCamera(true);
	}


	bool IsAnimationEnd();
	
	//애니메이션 생성
	void CreateAnimation(const FrameAnimationParameter& _Parameter);

	//애니메이션 변환
	void ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange = false);


	//(Actor의 CreateRender에서 호출)
	//렌더링 되는 순서 결정 및 Level의 Renders에 등록
	void SetOrder(int _Order) override;

	//이 함수를 통해 값을 설정하면 TextRender모드가 된다
	void SetText(const std::string_view& _Text);

protected:

private:
	//이미지 리소스와 연결된 GameEngineImage
	GameEngineImage*		Image					= nullptr;

	//이미지를 잘랐을때 그릴 이미지 인덱스
	int								Frame					= 0;

	//Render함수에서 TransparentBlt할때 지울 배경색상
	int								TransColor			= RGB(147, 187, 236);

	//렌더링 될 때 카메라에 영향을 받는지 여부
	bool								IsEffectCamera	= true;


	//이 값에 내용이 존재하면 TextRender를 실행
	std::string RenderText;

	//Level의 Render를 통해 실제 렌더링되는 함수
	void Render(float _DeltaTime);

	//렌더링 종류중 텍스트 렌더링
	void TextRender(float _DeltaTime);
	//렌더링 종류중 이미지 렌더링
	void ImageRender(float _DeltaTime);


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

		bool IsEnd();

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

