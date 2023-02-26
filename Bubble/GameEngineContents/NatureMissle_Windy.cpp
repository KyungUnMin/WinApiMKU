#include "NatureMissle_Windy.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "MonsterBase.h"
#include "RoundLevelBase.h"


const std::string_view NatureMissle_Windy::ImagePath				= "Windy.bmp";
const std::string_view NatureMissle_Windy::AniName					= "Windy";
const std::string_view NatureMissle_Windy::DestroyAniName	= "Destroy";


NatureMissle_Windy::NatureMissle_Windy()
{

}

NatureMissle_Windy::~NatureMissle_Windy()
{
	DragMonsters.clear();
}






void NatureMissle_Windy::Start()
{
	NatureMissleBase::Start();
	ResourceLoad();
	CreateAnimation();

	std::vector<GameEngineActor*> Monsters = GetRoundLevel()->GetAliveMonsters();
	if (true == Monsters.empty())
		return;

	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(Monsters.size() - 1));
	DestPos = Monsters[RandNum]->GetPos();
}



void NatureMissle_Windy::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("NatureMissle");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(3, 2);
	IsLoad = true;
}

void NatureMissle_Windy::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = ImagePath,
		.Start = 0,
		.End = 2
	});

	RenderPtr->CreateAnimation
	({
		.AnimationName = DestroyAniName,
		.ImageName = ImagePath,
		.Start = 3,
		.End = 5,
		.Loop = false
	});

	RenderPtr->ChangeAnimation(AniName);
}





void NatureMissle_Windy::Update(float _DeltaTime)
{
	Move(_DeltaTime);

	MonsterKill();
	MonsterDrag();

	if (false == ScreenOutCheck())
		return;

	for (MonsterBase* Monster : DragMonsters)
	{
		Monster->Off();
	}

	DragMonsters.clear();
	Death();
}



void NatureMissle_Windy::Move(float _DeltaTime)
{
	if (true == IsDestroy)
	{
		if (true == GetRender()->IsAnimationEnd())
		{
			Death();
		}

		return;
	}


	static const float FixedDirTime = 5.f;
	if (FixedDirTime < GetLiveTime())
	{
		SetMove(float4::Up * MoveSpeed * _DeltaTime);
		return;
	}

	//일정 시간마다 방향전환
	MoveAccTime += _DeltaTime;
	if (DirChangeTime < MoveAccTime)
	{
		MoveAccTime -= DirChangeTime;
		ChangeDirection();
	}

	SetMove(Dir * MoveSpeed * _DeltaTime);
}

void NatureMissle_Windy::ChangeDirection()
{
	static const float LowTime = 0.1f;
	static const float HighTime = 1.0f;

	DirChangeTime = GameEngineRandom::MainRandom.RandomFloat(LowTime, HighTime);
	IsHorizonMove = !IsHorizonMove;

	if (true == IsHorizonMove)
	{
		Dir = (GetPos().x < DestPos.x) ? float4::Right : float4::Left;
	}
	else
	{
		Dir = (GetPos().y < DestPos.y) ? float4::Down : float4::Up;
	}
}



void NatureMissle_Windy::MonsterKill()
{
	static std::vector<MonsterBase*> CollisionMonsters;
	if (false == CollisionCheckWithMonster(CollisionMonsters))
		return;

	for (MonsterBase* Monster : CollisionMonsters)
	{
		Monster->DeathFromNature(this);
		DragMonsters.push_back(Monster);
	}
}

void NatureMissle_Windy::MonsterDrag()
{
	auto Iter = DragMonsters.begin();
	while (Iter != DragMonsters.end())
	{
		if (false == (*Iter)->IsUpdate())
		{
			Iter = DragMonsters.erase(Iter);
			continue;
		}

		(*Iter)->SetPos(GetPos() + MonsterBase::CollisionOffset);
		++Iter;
	}
}


bool NatureMissle_Windy::ScreenOutCheck()
{
	static const float Offset = 50.f;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	float4 ThisPos = GetPos();

	if (ThisPos.x < -Offset)
		return true;

	if (ThisPos.y < -Offset)
		return true;

	if ((ScreenSize.x + Offset) < ThisPos.x)
		return true;

	if ((ScreenSize.y + Offset) < ThisPos.y)
		return true;

	return false;
}


void NatureMissle_Windy::DestroyByBoss()
{
	GetRender()->ChangeAnimation(DestroyAniName, true);
	IsDestroy = true;
	GetCollision()->Off();
}