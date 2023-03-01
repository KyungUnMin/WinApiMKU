#include "GhostTracer.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "BubbleDestHelper.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"
#include "BubbleCore.h"

const std::string_view	GhostTracer::RightImgPath		= "Right_Ghost.bmp";
const std::string_view	GhostTracer::LeftImgPath			= "Left_Ghost.bmp";
const std::string_view	GhostTracer::SmokeImgPath		= "GhostSmoke.bmp";

const std::string_view	GhostTracer::IdleAniName			= "Idle";
const std::string_view	GhostTracer::TraceAniName		= "Trace";

GhostTracer* GhostTracer::MainGhost = nullptr;

GhostTracer::GhostTracer()
{
	MainGhost = this;
	DebugPen = static_cast<HPEN>(CreatePen(PS_SOLID, 5, RGB(0, 0, 255)));
}

GhostTracer::~GhostTracer()
{
	if (this == MainGhost)
	{
		MainGhost = nullptr;
	}
	DeleteObject(DebugPen);
}



void GhostTracer::Start()
{
	ResourceLoad();
	CreateComponent();
	CreateAnimations();

	SetPos(BubbleDestHelper::GetGridPos(156));
	SetDir(float4::Left);
}


void GhostTracer::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Ghost");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImgPath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImgPath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SmokeImgPath))->Cut(5, 1);
	IsLoad = true;
}






void GhostTracer::CreateComponent()
{
	const float4 RenderScale = float4{ 200.f, 200.f };
	const float4 CollisionScale = float4{ 50.f, 50.f };

	SmokeRender = CreateRender(RenderOrder::BossLockBubble);
	SmokeRender->SetScale(RenderScale);
	GhostRender = CreateRender(RenderOrder::Monster2);
	GhostRender->SetScale(RenderScale);

	CollisionPtr = CreateCollision(CollisionOrder::GhostTracer);
	CollisionPtr->SetScale(CollisionScale);
}



void GhostTracer::CreateAnimations()
{
	SmokeRender->CreateAnimation
	({
		.AnimationName = "Smoke",
		.ImageName = SmokeImgPath,
		.Start = 0,
		.End = 4,
		.Loop = false
	});
	SmokeRender->ChangeAnimation("Smoke");

	//-----------------------------[Idle]-------------------

	std::string AniName;
	float Duration = 0.0f;

	Duration = 0.1f;
	AniName = MovableActor::RightStr + IdleAniName.data();
	GhostRender->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImgPath,
		.Start = 2,
		.End = 3,
		.InterTimer = Duration,
		.Loop = true
	});

	Duration = 0.1f;
	AniName = MovableActor::LeftStr + IdleAniName.data();
	GhostRender->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImgPath,
		.Start = 2,
		.End = 3,
		.InterTimer = Duration,
		.Loop = true
	});

	//-----------------------------[Trace]-------------------

	Duration = 0.1f;
	AniName = MovableActor::RightStr + TraceAniName.data();
	GhostRender->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = RightImgPath,
		.Start = 0,
		.End = 1,
		.InterTimer = Duration,
		.Loop = true
	});

	Duration = 0.1f;
	AniName = MovableActor::LeftStr + TraceAniName.data();
	GhostRender->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = LeftImgPath,
		.Start = 0,
		.End = 1,
		.InterTimer = Duration,
		.Loop = true
	});
}



void GhostTracer::SetDir(const float4& _Dir)
{
	MovableActor::SetDir(_Dir);
	std::string AniName = GetDirStr();

	switch (CurState)
	{
	case GhostTracer::State::Idle:
		AniName += IdleAniName;
		break;
	case GhostTracer::State::PlayerKill:
		return;
	default:
		AniName += TraceAniName;
		break;
	}

	GhostRender->ChangeAnimation(AniName);
}














void GhostTracer::Update(float _DeltaTime)
{
	Timer += _DeltaTime;

	switch (CurState)
	{
	case GhostTracer::State::Idle:
		Update_Idle(_DeltaTime);
		break;
	case GhostTracer::State::TraceY:
		Update_TraceY(_DeltaTime);
		break;
	case GhostTracer::State::TraceX:
		Update_TraceX(_DeltaTime);
		break;
	case GhostTracer::State::PlayerKill:
	{
		if (true == SmokeRender->IsAnimationEnd())
		{
			Death();
		}
	}
		return;
	}

	//플레이어 충돌
	PlayerCollisionCheck();
}


void GhostTracer::Update_Idle(float _DeltaTime)
{
	if (Timer < NowDuration)
		return;

	switch (PrevState)
	{
	case GhostTracer::State::TraceY:
		CurState = State::TraceX;
		break;
	case GhostTracer::State::TraceX:
		CurState = State::TraceY;
		break;
	}

	StartPos = GetPos();
	DestPos = StartPos;

	if (nullptr != PlayerBase::MainPlayer)
	{
		DestPos = (PlayerBase::MainPlayer->GetPos() + PlayerBase::CollisionOffset);
	}

	if (StartPos.x < DestPos.x)
	{
		SetDir(float4::Right);
	}
	else
	{
		SetDir(float4::Left);
	}

	Timer -= NowDuration;
}




void GhostTracer::Update_TraceY(float _DeltaTime)
{
	if ((0.f == NowDuration) && (nullptr != PlayerBase::MainPlayer))
	{
		SetPos(PlayerBase::MainPlayer->GetPos());
		return;
	}

	float4 LerpPos = CalcLerpDir();
	float4 NextPos = float4{ GetPos().x, LerpPos.y };
	SetPos(NextPos);

	if (Timer < NowDuration)
		return;

	PrevState = State::TraceY;
	CurState = State::Idle;
	Timer -= NowDuration;
	NowDuration *= NextDurPer;
	SetDir(GetDirVec());
}


void GhostTracer::Update_TraceX(float _DeltaTime)
{
	if ((0.f == NowDuration) && (nullptr != PlayerBase::MainPlayer))
	{
		SetPos(PlayerBase::MainPlayer->GetPos());
		return;
	}

	float4 LerpPos = CalcLerpDir();
	float4 NextPos = float4{ LerpPos.x, GetPos().y};
	SetPos(NextPos);

	if (Timer < NowDuration)
		return;

	PrevState = State::TraceX;
	CurState = State::Idle;
	Timer -= NowDuration;
	NowDuration *= NextDurPer;
	SetDir(GetDirVec());
}



const float4  GhostTracer::CalcLerpDir()
{
	if (nullptr == PlayerBase::MainPlayer)
	{
		return GetPos();
	}
	
	float Ratio = (Timer / NowDuration);
	return float4::LerpClamp(StartPos, DestPos, Ratio);
}

void GhostTracer::PlayerCollisionCheck()
{
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }))
		return;

	PlayerBase::MainPlayer->AttackPlayer();
}



void GhostTracer::KillPlayer()
{
	CurState = State::PlayerKill;
	SmokeRender->ChangeAnimation("Smoke", true);
	GhostRender->Off();
}







void GhostTracer::Render(float _DeltaTime)
{
	if (false == BubbleCore::GetInst().IsBossCheetOn())
		return;

	float4 DebugPos = DestPos;
	
	switch (CurState)
	{
	case GhostTracer::State::TraceY:
		DebugPos.x = StartPos.x;
		break;
	case GhostTracer::State::TraceX:
		DebugPos.y = StartPos.y;
		break;
	default:
		return;
	}

	DrawDebugArrow(GetPos(), DebugPos);
}





void GhostTracer::DrawDebugArrow(const float4& _Start, const float4& _End)
{
	const float ArrowLength = 30.f;

	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	DebugPen = static_cast<HPEN>(SelectObject(Hdc, DebugPen));

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

	DebugPen = static_cast<HPEN>(SelectObject(Hdc, DebugPen));
}