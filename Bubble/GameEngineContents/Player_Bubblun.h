#pragma once
#include "PlayerBase.h"

class Player_Bubblun : public PlayerBase
{
public:
	Player_Bubblun();
	~Player_Bubblun();

	Player_Bubblun(const Player_Bubblun& _Other) = delete;
	Player_Bubblun(Player_Bubblun&& _Other) noexcept = delete;
	Player_Bubblun& operator=(const Player_Bubblun& _Other) = delete;
	Player_Bubblun& operator=(const Player_Bubblun&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

