#include "BossState_Lock.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BossMonster.h"
#include "BossMonsterFSM.h"
#include "BossHpBar.h"


BossState_Lock::BossState_Lock()
{

}

BossState_Lock::~BossState_Lock()
{

}




void BossState_Lock::Start()
{
	const float4 LockBubbleScale = float4{ 150.f, 150.f };
	LockBubble = GetBoss()->CreateRender(BossMonster::LockBubbleImagePath, RenderOrder::BossLockBubble);
	LockBubble->SetScale(LockBubbleScale);
	LockBubble->Off();

	const float4 DestOffset = float4{ 0.f, -50.f };
	float4 ScreenCenter = GameEngineWindow::GetScreenSize().half();
	DestPos = (ScreenCenter + DestOffset);
}






void BossState_Lock::EnterState()
{
	GetBoss()->GetRender()->ChangeAnimation(BossMonster::LockAniName);

	LockBubble->On();
	StartPos = GetBoss()->GetPos();
	AccTime = 0.f;
}


void BossState_Lock::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	//�÷��̾�� �浹�ߴٸ� Pop���·� ����
	GameEngineCollision* CollisionPtr = GetBoss()->GetCollision();
	if (true == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }))
	{
		GetFSM()->ChangeState(BossStateType::Dead);
		return;
	}

	//Lock�ð��� ����Ͽ��� �������Ͱ� �ٽ� ��Ȱ�ϴ� ���
	if (LockTime < AccTime)
	{
		BossHpBar::MainBossHP->Revive();
		GetFSM()->ChangeState(BossStateType::Damaged);
		return;
	}

	Move();
}



void BossState_Lock::Move()
{
	float Ratio = (AccTime / LockTime);
	float4 NextPos = float4::LerpClamp(StartPos, DestPos, Ratio);
	GetBoss()->SetPos(NextPos);
}



void BossState_Lock::ExitState()
{
	LockBubble->Off();
}