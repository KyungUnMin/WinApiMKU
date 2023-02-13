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
	Player,
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

	Monster1,
	Monster2,

	AttackBubble,
	ClearBubble,
	Player1,

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