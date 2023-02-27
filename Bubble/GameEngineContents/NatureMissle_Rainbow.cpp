#include "NatureMissle_Rainbow.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "MonsterBase.h"

const std::string_view	NatureMissle_Rainbow::ImagePath			= "RainBow.bmp";
const float4					NatureMissle_Rainbow::CollisionScale		= float4{100.f, 100.f};
const float4					NatureMissle_Rainbow::CollisionOffset		= float4{ 75.f, -50.f };
const float4					NatureMissle_Rainbow::RenderScale			= float4{400.f, 400.f};

NatureMissle_Rainbow::NatureMissle_Rainbow()
{

}

NatureMissle_Rainbow::~NatureMissle_Rainbow()
{

}

void NatureMissle_Rainbow::DestroyByBoss()
{
	GetCollision()->Off();
	GameEngineResources::GetInst().SoundPlay("RainBowMade.wav");
}

void NatureMissle_Rainbow::Start()
{
	NatureMissleBase::Start();
	LoadSFX();
	ResourceLoad();

	GetRender()->SetScale(RenderScale);
	GetCollision()->SetScale(CollisionScale);
	GetCollision()->SetPosition(CollisionOffset);

	CreateAnimation();
}



void NatureMissle_Rainbow::LoadSFX()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Nature");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("RainBowMade.wav"));
	IsLoad = true;
}

void NatureMissle_Rainbow::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(9, 1);
	IsLoad = true;
}

void NatureMissle_Rainbow::CreateAnimation()
{
	GameEngineRender* RenderPtr = GetRender();
	RenderPtr->CreateAnimation
	({
		.AnimationName = "RainBow",
		.ImageName = ImagePath,
		.Start = 0,
		.End = 8,
		.InterTimer = 0.1f,
		.Loop = false
	});

	RenderPtr->ChangeAnimation("RainBow");
}




void NatureMissle_Rainbow::Update(float _DeltaTime)
{
	if (false == GetRender()->IsAnimationEnd())
		return;

	SetMove(float4::Down * MoveSpeed * _DeltaTime);
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	
	if ((ScreenSize.y + ScreenOutOffset.y) < GetPos().y)
	{
		Death();
		return;
	}

	static std::vector<MonsterBase*> Monsters;
	if (false == CollisionCheckWithMonster(Monsters))
		return;

	GameEngineResources::GetInst().SoundPlay("RainBowMade.wav");
	for (MonsterBase* Monster : Monsters)
	{
		Monster->DeathFromNature(this);
	}
}