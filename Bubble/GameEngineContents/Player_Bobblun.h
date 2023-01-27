#pragma once
#include "PlayerBase.h"

class Player_Bobblun : public PlayerBase
{
public:
	Player_Bobblun();
	~Player_Bobblun();

	Player_Bobblun(const Player_Bobblun& _Other) = delete;
	Player_Bobblun(Player_Bobblun&& _Other) noexcept = delete;
	Player_Bobblun& operator=(const Player_Bobblun& _Other) = delete;
	Player_Bobblun& operator=(const Player_Bobblun&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

