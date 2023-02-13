#pragma once
#include "MonsterStateBase.h"

class ZenChan_Falling : public MonsterStateBase
{
public:
	ZenChan_Falling();
	~ZenChan_Falling();

	ZenChan_Falling(const ZenChan_Falling& _Other) = delete;
	ZenChan_Falling(ZenChan_Falling&& _Other) noexcept = delete;
	ZenChan_Falling& operator=(const ZenChan_Falling& _Other) = delete;
	ZenChan_Falling& operator=(const ZenChan_Falling&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

protected:

private:
	const std::string_view FallingAniName	= "Falling";
	const std::string_view RageAniName		= "RageFalling";



	void CreateAnimation();
};

