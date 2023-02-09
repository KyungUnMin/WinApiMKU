#pragma once


enum class PlayerCharacterType
{
	BUBBLUN,
	BOBBLUN,
	KULULUN,
	CORORON,

	COUNT
};

enum class UpdateOrder
{
	Defalut,
	Player_Missle,
	BubbleDest,

	DEBUG_GRID
};

enum class RenderOrder
{
	BackGround1,
	BackGround2,
	BackGround3,

	Obstacle1,
	Obstacle2,

	Door,

	ClearBubble,
	Player1,

	AttackBubble,
	Monster1,
	Monster2,

};

enum class CollisionOrder
{
	Player,
	Door,
	Monster,
	Player_Missle,
	Monster_Missle,
	BubbleDest
};

enum class ComponentType
{
	//PlayerState,
	Gravity,
	BubbleSpawner,

	Count
};

enum class BubbleMissleType
{
	Normal,
	Fire,
	Water,
	Electronic,
	Rainbow,
	Windy,
	Melody
};