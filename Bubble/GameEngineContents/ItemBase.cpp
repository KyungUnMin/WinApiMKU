#include "ItemBase.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

const std::string_view	ItemBase::NormalImgPath				= "NormalItems.bmp";
const std::string_view	ItemBase::BubbleLiquidImgPath	= "BubbleLiquid.bmp";
const std::vector<std::string_view> ItemBase::ItemCreateSFX = 
{
	"ItemCreate0.wav",
	"ItemCreate1.wav",
	"ItemCreate2.wav",
	"ItemCreate3.wav",
	"ItemCreate4.wav",
	"ItemCreate5.wav",
	"ItemCreate6.wav"
};


const float4					ItemBase::CollisionScale					= float4{50.f, 50.f};
const float4					ItemBase::CollisionOffset				= float4{ 0.f, -25.f };
const float4					ItemBase::RenderScale					= float4{200.f, 200.f};

ItemBase::ItemBase()
{

}

ItemBase::~ItemBase()
{

}



void ItemBase::Start()
{
	ResourceLoad();
	LoadSFX();

	CollisionPtr = CreateCollision(CollisionOrder::Items);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);

	RenderPtr = CreateRender(RenderOrder::Items);
	RenderPtr->SetScale(RenderScale);

	int SFXIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(ItemCreateSFX.size() - 1));
	GameEngineResources::GetInst().SoundPlay(ItemCreateSFX[SFXIndex]);
}




void ItemBase::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Items");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(NormalImgPath))->Cut(10, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BubbleLiquidImgPath))->Cut(3, 1);
	IsLoad = true;
}

void ItemBase::LoadSFX()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Item");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("ItemEat.mp3"));

	for (size_t i = 0; i < ItemCreateSFX.size(); ++i)
	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName(ItemCreateSFX[i]));
	}

	IsLoad = true;
}


void ItemBase::Update(float _DeltaTime)
{
	//플레이어와 충돌할 때만
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }))
		return;
	
	GameEngineResources::GetInst().SoundPlay("ItemEat.mp3");
	Excute();
	Death();
}