#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>

enum class HelpLevelType
{
	RoundAEnter,
	RoundA1,
	RoundA2,
	RoundA3
};

class BubbleDestination;

class BubbleDestHelper : public GameEngineActor
{
public:
	static const std::vector<std::vector<int>> RoundAEnter;
	static const std::vector<std::vector<int>> RoundA1;
	static const std::vector<std::vector<int>> RoundA2;
	static const std::vector<std::vector<int>> RoundA3;

	static void RenderOnOffSwitch()
	{
		IsRenderOn = !IsRenderOn;
	}

	BubbleDestHelper();
	~BubbleDestHelper();

	BubbleDestHelper(const BubbleDestHelper& _Other) = delete;
	BubbleDestHelper(BubbleDestHelper&& _Other) noexcept = delete;
	BubbleDestHelper& operator=(const BubbleDestHelper& _Other) = delete;
	BubbleDestHelper& operator=(const BubbleDestHelper&& _Other) noexcept = delete;
	

	inline void SetOffset(const float4& _Offset)
	{
		Offset = _Offset;
	}

	//enum값을 입력받아 BubbleDestination을 생성하고 위치값 설정
	void SetBubbleDest(HelpLevelType _LevelType);


	//Dest의 이동경로 설정
	void ConnectDestToDest(size_t _Stage, size_t _Start, size_t _End);


	//BubbleDests 자료구조 상에서 지정한 스테이지의 BubbleDestination 벡터 반환
	std::vector<BubbleDestination*>& GetBubbleDest(size_t _Stage);

	//지정한 스테이지의 버블 목적지만 켜고 나머지는 끄기
	void TurnOnBubbleDest(size_t _Stage);

protected:
	void Start() override;
	void Render(float _DeltaTime) override;

private:
	static bool		IsRenderOn;

	float4				ScreenSize		= float4::Zero;
	float4				Offset				= float4::Zero;

	const int			WidthCount		= 32;
	const int			HeightCount	= 24;

	HPEN				GridPen			= HPEN();



	std::vector<std::vector<BubbleDestination*>> BubbleDests;

	//enum을 받아 static const std::vector<std::vector<int>>를 반환
	const std::vector<std::vector<int>>& GetData(HelpLevelType _LevelType);

	//그리드의 인덱스값을 화면의 좌표로 변경
	float4 GetPointPos(int _Index);
};

