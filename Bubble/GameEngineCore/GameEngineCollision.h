#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"

//충돌 처리 타입
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
	//TargetGroup은 반드시 지정시키기 위해 아무 숫자나 넣음
	int					TargetGroup		= -2374856;
	CollisionType	TargetColType	= CollisionType::CT_Circle;
	CollisionType	ThisColType		= CollisionType::CT_Circle;
};



class GameEngineCollision : public GameEngineComponent
{
public:
	//원과 원 충돌
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

	//자신이 상대 그룹과 충돌했는지 여부를 알려주는 함수
	bool Collision(const CollisionCheckParameter& _Parameter);

	//자신이 상대 그룹과 충돌했다면 vector에 충돌한 Collision을 담아서 돌려주는 함수
	bool Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision);


	//(Actor의 CreateCollision에서만 호출)
	//충돌 그룹 결정 및 Level의 Collisions에 등록
	void SetOrder(int _Order) override;

	//Posiion과 Scale 반환
	CollisionData GetCollisionData();

	void SetDebugRenderType(CollisionType _DebugRenderType)
	{
		DebugRenderType = _DebugRenderType;
	}

	//디버그 상태일때 충돌체의 영역을 그리는 함수
	void DebugRender();

protected:

private:
	CollisionType DebugRenderType = CollisionType::CT_Circle;
};

