#include "BossStateBase.h"
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BossMonsterFSM.h"
#include "BossMonster.h"
#include "PlayerBase.h"
#include "NatureMissleBase.h"
#include "BossHpBar.h"

BossStateBase::BossStateBase()
{
}

BossStateBase::~BossStateBase()
{
}


BossMonster* BossStateBase::GetBoss()
{
	return FsmPtr->GetBoss();
}


void BossStateBase::ChangeAniDir(const std::string_view& _AniName)
{
	BossMonster* BossPtr = FsmPtr->GetBoss();
	GameEngineRender* RenderPtr = BossPtr->GetRender();

	std::string NextAniName = BossPtr->GetDirStr();
	NextAniName += _AniName;
	RenderPtr->ChangeAnimation(NextAniName, true);
}

void BossStateBase::CheckCollisionWithPlayer()
{
	if (nullptr == PlayerBase::MainPlayer)
		return;
	
	GameEngineCollision* CollisionPtr = GetBoss()->GetCollision();
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }))
		return;

	PlayerBase::MainPlayer->AttackPlayer();
}


int BossStateBase::CheckCollisionWithNatureMissle()
{
	static std::vector<GameEngineCollision*> NatureMissles;
	GameEngineCollision* CollisionPtr = GetBoss()->GetCollision();
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::NatureMissle) }, NatureMissles))
		return 0;

	for (GameEngineCollision* NatureCollision : NatureMissles)
	{
		NatureMissleBase* Nature = dynamic_cast<NatureMissleBase*>(NatureCollision->GetActor());
		if (nullptr == Nature)
		{
			MsgAssert("CollisionOrder::NatureMissle에 NatureMissleBase를 상속받지 않은 엑터가 존재합니다");
			return 0;
		}

		Nature->DestroyByBoss();
	}

	return static_cast<int>(NatureMissles.size());
}

void BossStateBase::DrawDebugArrow(const float4& _Start, const float4& _End)
{
	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	const float ArrowLength = 30.f;

	float4 ReverseDir = _Start - _End;
	if (0.f == ReverseDir.Size())
		return;


	MoveToEx(Hdc, _Start.ix(), _Start.iy(), nullptr);
	LineTo(Hdc, _End.ix(), _End.iy());

	ReverseDir.Normalize();

	float4 RightArrowPos = _End + (ReverseDir.RotationZDegReturn(30.f) * ArrowLength);
	MoveToEx(Hdc, _End.ix(), _End.iy(), nullptr);
	LineTo(Hdc, RightArrowPos.ix(), RightArrowPos.iy());

	float4 LeftArrowPos = _End + (ReverseDir.RotationZDegReturn(-30.f) * ArrowLength);
	MoveToEx(Hdc, _End.ix(), _End.iy(), nullptr);
	LineTo(Hdc, LeftArrowPos.ix(), LeftArrowPos.iy());

}

