#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>

class  GameEngineLevel;

class BubbleMissle : public GameEngineActor
{
	friend GameEngineLevel;

public:
	static BubbleMissle* Instance;

	static BubbleMissle* Create(int _Order = 0);

	static void Destroy(BubbleMissle* _Bubble);

	static void Release();



	

	BubbleMissle(const BubbleMissle& _Other) = delete;
	BubbleMissle(BubbleMissle&& _Other) noexcept = delete;
	BubbleMissle& operator=(const BubbleMissle& _Other) = delete;
	BubbleMissle& operator=(const BubbleMissle&& _Other) noexcept = delete;

	void Start() override;


protected:

private:
	static std::vector<BubbleMissle*> Pool;

	BubbleMissle();
	~BubbleMissle();
};

