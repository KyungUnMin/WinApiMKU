#include "GameEngineCollision.h"
#include <list>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>


//CT_Max * CT_Max 전역함수 포인터
bool (*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);

//ColFunctionPtr 함수포인터를 초기화 하는 용도로만 쓰는 Cpp파일의 클래스
class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		ColFunctionPtr[CT_Circle][CT_Circle] = GameEngineCollision::CollisionCircleToCircle;
	}

	~CollisionFunctionInit()
	{

	}
};

//생성 시켜 주어야 ColFunctionPtr 배열에 값이 초기화된다
CollisionFunctionInit Init;



GameEngineCollision::GameEngineCollision()
{

}

GameEngineCollision::~GameEngineCollision()
{

}

//원과 원 충돌
bool GameEngineCollision::CollisionCircleToCircle(const CollisionData& _Left, const CollisionData& _Right)
{
	//두 물체 사이의 거리
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();

	//두 물체의 반지름의 합(Scale의 x를 지름으로 본다)
	float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();

	//두 물체의 거리가 반지름의 합 보다 작다면 충돌했다
	return Size < RadiusSum;
}



void GameEngineCollision::SetOrder(int _Order)
{
	GameEngineComponent::SetOrder(_Order);

	//(Collision객체를 Level와 Actor의 자료구조, 두 곳에서 관리한다)
	// 생성 및 소멸은 Actor, Update는 Level
	//GameEngineLevel의 Collisions에 등록
	GetActor()->GetLevel()->PushCollision(this);
}



//자신이 상대 그룹과 충돌했는지 여부를 알려주는 함수
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	//충돌확인할 상대방그룹을 가져온다
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌타입입니다");
		}

		//충돌한 경우 true 반환
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}

	//아무것도 충돌하지 않음
	return false;
}

//자신이 상대 그룹과 충돌했다면 vector에 충돌한 Collision을 담아서 돌려주는 함수
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	//충돌확인할 상대방그룹을 가져온다
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌타입입니다");
		}

		//충돌한 경우 벡터에 보관
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			_Collision.push_back(OtherCollision);
		}
	}

	//벡터에 아무것도 없다면 false, 존재한다면 true
	return _Collision.size() != 0;
}




CollisionData GameEngineCollision::GetCollisionData()
{
	return { GetActorPlusPos(), GetScale() };
}

