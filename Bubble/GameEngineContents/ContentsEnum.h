#pragma once


enum class PlayerCharacterType
{
	BUBBLUN,
	BOBBLUN,
	KULULUN,
	CORORON,
};

enum class RoundRenderOrder
{
	BackGround1,
	BackGround2,
	BackGround3,

	Obstacle1,
	Obstacle2,

	Door,

	ClearBubble,
	Player1,
	Player2,

	Monster1,
	Monster2,
	AttackBubble,

};

enum class ComponentType
{
	PlayerState,
	Gravity,

	Count
};