#include "MonsterState_PuruFly.h"
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterBase.h"
#include "RoundLevelBase.h"
#include "PlayerBase.h"

const std::string_view MonsterState_PuruFly::AniNames[2] = { "UpFly", "DownFly" };

MonsterState_PuruFly::MonsterState_PuruFly()
{

}

MonsterState_PuruFly::~MonsterState_PuruFly()
{

}

void MonsterState_PuruFly::Start()
{
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetMonster()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("���Ͱ� RoundLevel�� �ƴ� ������ �����Ǿ����ϴ�");
		return;
	}

	if (MoveDir::Up == CurState)
	{
		NowDir.y = -1.f;
	}
	else if(MoveDir::Down == CurState)
	{
		NowDir.y = 1.f;
	}

	NowDir.Normalize();
}

void MonsterState_PuruFly::EnterState()
{
	AnimationChange();
}

void MonsterState_PuruFly::Update(float _DeltaTime)
{
	//�÷��̾� �浹 ó��
	if (true == PlayerCollisionCheck())
	{
		PlayerBase::MainPlayer->AttackPlayer();
	}

	float4 NowPos = GetMonster()->GetPos();
	float4 NextPos = NowPos + (NowDir * MoveSpeed * _DeltaTime);
	float4 ColScale = MonsterBase::CollisionScale.half();

	//���� ���� ������ �ʾҴٸ� �̵���Ű�� return
	if (false == RoundLevel->IsBlockPos(NextPos + (ColScale * NowDir)))
	{
		GetMonster()->SetPos(NextPos);
		return;
	}

	const float PrevDirY = NowDir.y;
	
	//���� ȸ��
	float Radian = -30.f * GameEngineMath::DegToRad;
	float4 NextDir = float4::Zero;
	NextDir.x = NowDir.x * cosf(Radian) - NowDir.y * sinf(Radian);
	NextDir.y = NowDir.x * sinf(Radian) + NowDir.y * cosf(Radian);
	NowDir = NextDir;

	//Y���� �ٲ������
	if (0.f < (NowDir.y * PrevDirY))
		return;

	AnimationChange();
}



void MonsterState_PuruFly::AnimationChange()
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();

	CurState = (CurState == MoveDir::Up) ? MoveDir::Down : MoveDir::Up;
	RenderPtr->ChangeAnimation(AniNames[static_cast<int>(CurState)]);
}
