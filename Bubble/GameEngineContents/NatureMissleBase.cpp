#include "NatureMissleBase.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"
#include "PlayerBase.h"
#include "MonsterBase.h"

const										float4 NatureMissleBase::CollisionScale		= float4{50.f, 50.f};
const										float4 NatureMissleBase::RenderScale			= float4{200.f, 200.f};

NatureMissleBase::NatureMissleBase()
{

}

NatureMissleBase::~NatureMissleBase()
{

}

void NatureMissleBase::AllMissleClear()
{

}


void NatureMissleBase::Start()
{
	MovableActor::Start();
	RenderPtr = CreateRender(RenderOrder::NatureMissle);
	RenderPtr->SetScale(RenderScale);

	CollisionPtr = CreateCollision(CollisionOrder::NatureMissle);
	CollisionPtr->SetScale(CollisionScale);

	//�����ɶ� �÷��̾� ����� �ݴ� �������� �����ȴ�
	if (nullptr != PlayerBase::MainPlayer)
	{
		float4 PlayerDir = PlayerBase::MainPlayer->GetDirVec();
		float4 ThisDir = { -PlayerDir.x, PlayerDir.y };
		SetDir(ThisDir);
	}
	
}





bool NatureMissleBase::CollisionCheckWithPlayer()
{
	if (nullptr == PlayerBase::MainPlayer)
		return false;

	//�÷��̾ ��������� ��
	if (true == PlayerBase::IsUnbeatable())
		return false;

	float4 PlayerPos = PlayerBase::MainPlayer->GetPos();
	float4 PlayerColScale = PlayerBase::CollisionScale;
	float4 ThisPos = GetPos();
	float4 ThisColScale = CollisionScale;

	return GameEngineCollision::CollisionCircleToCircle({ PlayerPos, PlayerColScale }, { ThisPos , ThisColScale });
}



bool NatureMissleBase::CollisionCheckWithMonster(std::vector<MonsterBase*>& _Monsters)
{
	_Monsters.clear();

	static std::vector<GameEngineCollision*> MonsterCollisions;
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Monster) }, MonsterCollisions))
		return false;

	_Monsters.reserve(MonsterCollisions.size());
	for (GameEngineCollision* MonsterCol : MonsterCollisions)
	{
		MonsterBase* Monster = dynamic_cast<MonsterBase*>(MonsterCol->GetActor());
		if (nullptr == Monster)
		{
			MsgAssert("CollisionOrder::Monster�� ���Ͱ� �ƴ� ��ü�� �����߽��ϴ�");
			return false;
		}

		//������ �����ְų� �̹� �װ� �ִ� ���ʹ� �浹ó������ ����
		if (true == Monster->IsLocked())
			continue;

		_Monsters.push_back(Monster);
	}

	return true;
}
