#pragma once


enum class PlayerCharacterType
{
	BUBBLUN,
	BOBBLUN,
	KULULUN,
	CORORON,

	COUNT
};

//���ʹ� �׻� Bubble���� �ʰ� ����Ǿ�� �մϴ�
//�׷��� ������ Death�ɶ� ��۸� �����͸� ������ �ֽ��ϴ�
//������ ������ �ݸ����� �ξ ������ ��ȹ�Դϴ�
enum class UpdateOrder
{
	Defalut,
	Player,
	Player_Missle,
	Monster,
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

	AttackBubble,
	Monster1,
	Monster2,

	ClearBubble,
	Player1,

	UI
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

enum class MonsterType
{
	ZenChan,

};