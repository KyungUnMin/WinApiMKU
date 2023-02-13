#pragma once
#include "MonsterStateBase.h"

class RoundLevelBase;

class ZenChan_Move : public MonsterStateBase
{
public:
	static const float MoveSpeed;

	ZenChan_Move();
	~ZenChan_Move() override;

	ZenChan_Move(const ZenChan_Move& _Other) = delete;
	ZenChan_Move(ZenChan_Move&& _Other) noexcept = delete;
	ZenChan_Move& operator=(const ZenChan_Move& _Other) = delete;
	ZenChan_Move& operator=(const ZenChan_Move&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

protected:
	

private:
	const std::string_view	MoveAniName		= "Move";
	const std::string_view	RageAniName		= "RageMove";
	RoundLevelBase*			RoundLevel			= nullptr;

	void CreateAnimation();
	void ChangeDir();
};

