#include "GameEngineCollision.h"
#include <list>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>


//CT_Max * CT_Max �����Լ� ������
bool (*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);

//ColFunctionPtr �Լ������͸� �ʱ�ȭ �ϴ� �뵵�θ� ���� Cpp������ Ŭ����
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

//���� ���� �־�� ColFunctionPtr �迭�� ���� �ʱ�ȭ�ȴ�
CollisionFunctionInit Init;



GameEngineCollision::GameEngineCollision()
{

}

GameEngineCollision::~GameEngineCollision()
{

}

//���� �� �浹
bool GameEngineCollision::CollisionCircleToCircle(const CollisionData& _Left, const CollisionData& _Right)
{
	//�� ��ü ������ �Ÿ�
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();

	//�� ��ü�� �������� ��(Scale�� x�� �������� ����)
	float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();

	//�� ��ü�� �Ÿ��� �������� �� ���� �۴ٸ� �浹�ߴ�
	return Size < RadiusSum;
}



void GameEngineCollision::SetOrder(int _Order)
{
	GameEngineComponent::SetOrder(_Order);

	//(Collision��ü�� Level�� Actor�� �ڷᱸ��, �� ������ �����Ѵ�)
	// ���� �� �Ҹ��� Actor, Update�� Level
	//GameEngineLevel�� Collisions�� ���
	GetActor()->GetLevel()->PushCollision(this);
}



//�ڽ��� ��� �׷�� �浹�ߴ��� ���θ� �˷��ִ� �Լ�
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	//�浹Ȯ���� ����׷��� �����´�
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("���� �浹�Լ��� ������ ���� �浹Ÿ���Դϴ�");
		}

		//�浹�� ��� true ��ȯ
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}

	//�ƹ��͵� �浹���� ����
	return false;
}

//�ڽ��� ��� �׷�� �浹�ߴٸ� vector�� �浹�� Collision�� ��Ƽ� �����ִ� �Լ�
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	//�浹Ȯ���� ����׷��� �����´�
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("���� �浹�Լ��� ������ ���� �浹Ÿ���Դϴ�");
		}

		//�浹�� ��� ���Ϳ� ����
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			_Collision.push_back(OtherCollision);
		}
	}

	//���Ϳ� �ƹ��͵� ���ٸ� false, �����Ѵٸ� true
	return _Collision.size() != 0;
}




CollisionData GameEngineCollision::GetCollisionData()
{
	return { GetActorPlusPos(), GetScale() };
}

