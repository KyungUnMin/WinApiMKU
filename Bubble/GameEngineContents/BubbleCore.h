#pragma once
#include <GameEngineCore/GameEngineCore.h>

//BubbleCore�� �� �ϳ��� �����ؾ� �ϱ� ������
//�̱������� ����
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

protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	BubbleCore();
	~BubbleCore();
	
	static BubbleCore Core;
};

