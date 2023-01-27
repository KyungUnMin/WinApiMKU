#pragma once
#include "PlayerBase.h"

class Player_Kululun : public PlayerBase
{
public:
	Player_Kululun();
	~Player_Kululun();

	Player_Kululun(const Player_Kululun& _Other) = delete;
	Player_Kululun(Player_Kululun&& _Other) noexcept = delete;
	Player_Kululun& operator=(const Player_Kululun& _Other) = delete;
	Player_Kululun& operator=(const Player_Kululun&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

