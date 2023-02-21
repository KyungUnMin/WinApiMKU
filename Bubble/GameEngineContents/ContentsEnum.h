#pragma once


enum class PlayerCharacterType
{
	BUBBLUN,
	BOBBLUN,
	KULULUN,
	CORORON,

	COUNT
};

//몬스터는 항상 Bubble보다 늦게 실행되어야 합니다
//그래야 버블이 Death될때 댕글링 포인터를 막을수 있습니다
//하지만 버블에도 콜리전을 두어서 개선할 계획입니다

//NatureMissle은 Monster보다 늦게 실행되어야 함
//그래야 Nature가 Monster의 이동을 컨트롤 할 수 있음
enum class UpdateOrder
{
	Defalut,
	Player,
	Player_Missle,
	Monster_Missle,
	Monster,
	BubbleDest,
	Nature_Missle,

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

	AttackBubble,
	Monster_Missle,
	Monster1,
	Monster2,

	ClearBubble,
	Player1,
	NatureMissle,

	UI
};

enum class CollisionOrder
{
	Player,
	Door,
	Monster,
	Player_Missle,
	Monster_Missle,
	BubbleDest,
	NatureMissle,
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
