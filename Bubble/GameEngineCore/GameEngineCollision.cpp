#include "GameEngineCollision.h"
#include <list>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
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
		ColFunctionPtr[CT_Circle][CT_Point] = GameEngineCollision::CollisionCircleToPoint;
		ColFunctionPtr[CT_Rect][CT_Rect] = GameEngineCollision::CollisionRectToRect;
		ColFunctionPtr[CT_Rect][CT_Point] = GameEngineCollision::CollisionRectToPoint;
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


//���� �� �浹
bool GameEngineCollision::CollisionCircleToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	//�� ��ü ������ �Ÿ�
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();

	//���� ������(Scale�� x�� �������� ����)
	float RadiusSum = _Left.Scale.hx();

	//�� ��ü�� �Ÿ��� ���������� �۴ٸ� �浹�ߴ�
	return Size < RadiusSum;
}


//�簢���� �簢�� �浹
bool GameEngineCollision::CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Top())
	{
		return false;
	}

	if (_Left.Top() >= _Right.Bot())
	{
		return false;
	}

	if (_Left.Left() >= _Right.Right())
	{
		return false;
	}

	if (_Left.Right() <= _Right.Left())
	{
		return false;
	}

	return true;
}


//�簢���� �� �浹
bool GameEngineCollision::CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Top() >= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Left() >= _Right.Position.x)
	{
		return false;
	}

	if (_Left.Right() <= _Right.Position.x)
	{
		return false;
	}

	return true;
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
	if (false == IsUpdate())
	{
		return false;
	}

	//�浹Ȯ���� ����׷��� �����´�
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (this == OtherCollision)
		{
			continue;
		}

		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		OtherCollision->SetDebugRenderType(OtherType);

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
	if (false == IsUpdate())
	{
		return false;
	}
	
	_Collision.clear();

	//�浹Ȯ���� ����׷��� �����´�
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (this == OtherCollision)
		{
			continue;
		}

		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		OtherCollision->SetDebugRenderType(OtherType);

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

void GameEngineCollision::DebugRender()
{
	HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

	//�� ������Ʈ�� ������ + ������ ī�޶� ��ġ
	float4 DebugRenderPos = GetActorPlusPos() - GetActor()->GetLevel()->GetCameraPos();

	switch (DebugRenderType)
	{
	case CT_Point:
		break;
	case CT_Circle:
	{
		int Radius = GetScale().hix();
		Ellipse(BackBufferDc, 
			DebugRenderPos.ix() - Radius,
			DebugRenderPos.iy() - Radius,
			DebugRenderPos.ix() + Radius,
			DebugRenderPos.iy() + Radius);
		break;
	}
	case CT_Rect:
		Rectangle(BackBufferDc,
			DebugRenderPos.ix() - GetScale().hix(),
			DebugRenderPos.iy() - GetScale().hiy(),
			DebugRenderPos.ix() + GetScale().hix(),
			DebugRenderPos.iy() + GetScale().hiy());
		break;
	case CT_Max:
		break;
	default:
		break;
	}
}

