#pragma once
#include <GameEngineCore/GameEngineActor.h>

class SelectPlayerBackGround : public GameEngineActor
{
public:
	SelectPlayerBackGround();
	~SelectPlayerBackGround();

	SelectPlayerBackGround(const SelectPlayerBackGround& _Other) = delete;
	SelectPlayerBackGround(SelectPlayerBackGround&& _Other) noexcept = delete;
	SelectPlayerBackGround& operator=(const SelectPlayerBackGround& _Other) = delete;
	SelectPlayerBackGround& operator=(const SelectPlayerBackGround&& _Other) noexcept = delete;

protected:


private:

};

