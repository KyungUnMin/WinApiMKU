#pragma once
#include "PlayerBase.h"


class Player_Cororon : public PlayerBase
{
public:
	Player_Cororon();
	~Player_Cororon();

	Player_Cororon(const Player_Cororon& _Other) = delete;
	Player_Cororon(Player_Cororon&& _Other) noexcept = delete;
	Player_Cororon& operator=(const Player_Cororon& _Other) = delete;
	Player_Cororon& operator=(const Player_Cororon&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

