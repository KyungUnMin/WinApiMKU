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

	//생성될때 플레이어 방향과 반대 방향으로 설정된다
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

	//플레이어가 무적모드일 때
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
			MsgAssert("CollisionOrder::Monster에 몬스터가 아닌 객체가 존재했습니다");
			return false;
		}

		//버블이 갖혀있거나 이미 죽고 있는 몬스터는 충돌처리하지 않음
		if (true == Monster->IsLocked())
			continue;

		_Monsters.push_back(Monster);
	}

	return true;
}
