#include "Item_BossJewellery.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

const std::string_view Item_BossJewellery::ImagePath = "BossJewellery.bmp";

Item_BossJewellery::Item_BossJewellery()
{

}

Item_BossJewellery::~Item_BossJewellery()
{

}

void Item_BossJewellery::Start()
{
	ItemBase::Start();
	ResourceLoad();
	CreateAnimation();
	Item_GravityNormal::ConnectRoundLevel();
	Item_GravityNormal::SetStartSpeed(StartSpeed);
}



void Item_BossJewellery::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("Reward");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(4, 1);
	IsLoad = true;
}

void Item_BossJewellery::CreateAnimation()
{
	const std::string_view AniName = "Jewellery";
	GameEngineRender* RenderPtr = GetRender();

	RenderPtr->CreateAnimation
	({
		.AnimationName = AniName,
		.ImageName = ImagePath,
		.Start = 0,
		.End = 3,
		.InterTimer = 0.15f,
		.Loop = true
	});

	RenderPtr->ChangeAnimation(AniName);
	RenderPtr->SetScale(RenderScale);
}


void Item_BossJewellery::Update(float _DeltaTime)
{
	Item_GravityNormal::Update(_DeltaTime);
}