#include "ItemBase.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"
#include "RoundLevelBase.h"

const std::string_view	ItemBase::NormalImgPath		= "NormalItems.bmp";
const float4					ItemBase::CollisionScale			= float4{50.f, 50.f};
const float4					ItemBase::CollisionOffset		= float4{ 0.f, -25.f };
const float4					ItemBase::RenderScale			= float4{200.f, 200.f};

ItemBase::ItemBase()
{

}

ItemBase::~ItemBase()
{

}



void ItemBase::Start()
{
	ResourceLoad();

	CollisionPtr = CreateCollision(CollisionOrder::Items);
	CollisionPtr->SetScale(CollisionScale);
	CollisionPtr->SetPosition(CollisionOffset);

	RenderPtr = CreateRender(RenderOrder::Items);
	RenderPtr->SetScale(RenderScale);
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
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(NormalImgPath))->Cut(10, 9);
	IsLoad = true;
}




void ItemBase::Init(const float4& _Pos)
{
	RoundLevelBase* RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("아이템이 RoundLevel이 아닌곳에서 생성되었습니다");
		return;
	}

	float4 Pos = _Pos;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();


	while (false == RoundLevel->IsBlockPos(Pos))
	{
		Pos += float4::Down;

		if (ScreenSize.y < Pos.y)
		{
			Pos.y = 50.f;
		}
	}

	SetPos(Pos);
}




void ItemBase::Update(float _DeltaTime)
{
	//플레이어와 충돌할 때만
	if (false == CollisionPtr->Collision({ .TargetGroup = static_cast<int>(CollisionOrder::Player) }))
		return;
	
	Excute();
	Death();
}