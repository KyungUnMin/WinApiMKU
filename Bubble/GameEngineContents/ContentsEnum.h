#pragma once


enum class PlayerCharacterType
{
	BUBBLUN,
	BOBBLUN,
	KULULUN,
	CORORON,
	COUNT
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

	Monster1,
	Monster2,
	AttackBubble,

};

enum class CollisionOrder
{
	Player,
	Door,
	Monster,
	Player_Missle,
	Monster_Missle
};

enum class ComponentType
{
	PlayerState,
	Gravity,
	BubbleSpawner,

	Count
};

