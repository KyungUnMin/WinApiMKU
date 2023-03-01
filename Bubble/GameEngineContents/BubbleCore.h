#pragma once
#include <GameEngineCore/GameEngineCore.h>

//BubbleCore는 단 하나만 존재해야 하기 때문에
//싱글톤으로 구현
class BubbleCore : public GameEngineCore
{
public:
	static BubbleCore& GetInst()
	{
		return Core;
	}

	BubbleCore(const BubbleCore& _Other) = delete;
	BubbleCore(BubbleCore&& _Other) noexcept = delete;
	BubbleCore& operator=(const BubbleCore& _Other) = delete;
	BubbleCore& operator=(const BubbleCore&& _Other) noexcept = delete;

	inline bool IsBossCheetOn()
	{
		return BossCheekOn;
	}

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	static BubbleCore	Core;
	HPEN						DebugPen			= HPEN();
	HBRUSH					DebugBrush			= HBRUSH();

	bool							BossCheekOn		= false;


	BubbleCore();
	~BubbleCore();

	void CreateDebugPenBrush();
	void CreateLevels();
	void CreateKeys();
};

