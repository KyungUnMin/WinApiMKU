#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"

//�浹 ó�� Ÿ��
enum CollisionType
{
	CT_Point,
	CT_Circle,
	CT_Rect,

	CT_Max
};

class CollisionCheckParameter
{
public:
	//TargetGroup�� �ݵ�� ������Ű�� ���� �ƹ� ���ڳ� ����
	int					TargetGroup		= -2374856;
	CollisionType	TargetColType	= CollisionType::CT_Circle;
	CollisionType	ThisColType		= CollisionType::CT_Circle;
};



class GameEngineCollision : public GameEngineComponent
{
public:
	//���� �� �浹
	static bool CollisionCircleToCircle(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionCircleToPoint(const CollisionData& _Left, const CollisionData& _Right);

	static bool CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right);



	GameEngineCollision();
	~GameEngineCollision();

	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision&& _Other) noexcept = delete;

	//�ڽ��� ��� �׷�� �浹�ߴ��� ���θ� �˷��ִ� �Լ�
	bool Collision(const CollisionCheckParameter& _Parameter);

	//�ڽ��� ��� �׷�� �浹�ߴٸ� vector�� �浹�� Collision�� ��Ƽ� �����ִ� �Լ�
	bool Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision);


	//(Actor�� CreateCollision������ ȣ��)
	//�浹 �׷� ���� �� Level�� Collisions�� ���
	void SetOrder(int _Order) override;

	//Posiion�� Scale ��ȯ
	CollisionData GetCollisionData();

	void SetDebugRenderType(CollisionType _DebugRenderType)
	{
		DebugRenderType = _DebugRenderType;
	}

	//����� �����϶� �浹ü�� ������ �׸��� �Լ�
	void DebugRender();

protected:

private:
	CollisionType DebugRenderType = CollisionType::CT_Circle;
};

