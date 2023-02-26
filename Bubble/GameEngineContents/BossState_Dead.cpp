#include "BossState_Dead.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "BossMonster.h"
#include "BossMonsterFSM.h"
#include "BossDeadEffect.h"

BossState_Dead::BossState_Dead()
{

}

BossState_Dead::~BossState_Dead()
{

}


//PopEffect = GetBoss()->CreateRender(RenderOrder::)
	//Pop ����Ʈ�� ������ ������Ʈ�� ������ �ű⿣ Point & ����Pop����Ʈ�� ��������
void BossState_Dead::EnterState()
{
	BossMonster* Boss = GetBoss();
	GameEngineRender* RenderPtr = Boss->GetRender();
	RenderPtr->ChangeAnimation(BossMonster::DeadAniName);
	RenderPtr->SetOrder(static_cast<int>(RenderOrder::UI));

	SelectDirection();

	BossDeadEffect* DeadEffect = Boss->GetLevel()->CreateActor<BossDeadEffect>(UpdateOrder::PointEffect);
	DeadEffect->SetPos(Boss->GetPos());
}

void BossState_Dead::SelectDirection()
{
	ScreenSize = GameEngineWindow::GetScreenSize();

	NowSpeed = StartSpeed;
	float4 ThisPos = GetBoss()->GetPos();

	if (ScreenSize.hx() < ThisPos.x)
	{
		NowSpeed.x = -StartSpeed.x;
	}
}


void BossState_Dead::Update(float _DeltaTime)
{
	NowSpeed.y += (Gravity * _DeltaTime);
	GetBoss()->SetMove(NowSpeed * _DeltaTime);

	float4 ThisPos = GetBoss()->GetPos();
	if ((ScreenSize.y + ScreenOutOffset.y) < ThisPos.y)
	{
		GetBoss()->Death();
	}
}

