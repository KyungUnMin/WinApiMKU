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

	//enum���� �Է¹޾� BubbleDestination�� �����ϰ� ��ġ�� ����
	void SetBubbleDest(HelpLevelType _LevelType);


	//Dest�� �̵���� ����
	void ConnectDestToDest(size_t _Stage, size_t _Start, size_t _End);


	//BubbleDests �ڷᱸ�� �󿡼� ������ ���������� BubbleDestination ���� ��ȯ
	std::vector<BubbleDestination*>& GetBubbleDest(size_t _Stage);

	//������ ���������� ���� �������� �Ѱ� �������� ����
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

	//enum�� �޾� static const std::vector<std::vector<int>>�� ��ȯ
	const std::vector<std::vector<int>>& GetData(HelpLevelType _LevelType);

	//�׸����� �ε������� ȭ���� ��ǥ�� ����
	float4 GetPointPos(int _Index);
};

