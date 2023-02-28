#include "BossDeadBox.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "Item_GravityNormal.h"
#include "Item_BossJewellery.h"

const std::string_view BossDeadBox::ImagePath = "BossDeadBox.bmp";

BossDeadBox::BossDeadBox()
{

}

BossDeadBox::~BossDeadBox()
{

}

void BossDeadBox::Start()
{
	ResourceLoad();

	const float4 RenderScale = float4{ 400.f, 400.f };
	RenderPtr = CreateRender(ImagePath, RenderOrder::RewardBox);
	RenderPtr->SetScale(RenderScale);
	RenderPtr->SetFrame(static_cast<int>(State::Close));
}


void BossDeadBox::ResourceLoad()
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(2, 1);
	IsLoad = true;
}




void BossDeadBox::Update(float _DeltaTime)
{
	switch (NowState)
	{
	case BossDeadBox::State::Close:
		Update_Close();
		break;
	case BossDeadBox::State::Open:
		Update_Open(_DeltaTime);
		break;
	}
}

void BossDeadBox::Update_Close()
{
	const float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float4 StartPos = { ScreenSize.hx(), 0.f };
	const float4 EndPos = { ScreenSize.hx(), ScreenSize.y - 20.f };
	const float OpenTime = 1.5f;

	float Timer = GetLiveTime();
	float Ratio = (Timer / OpenTime);
	float4 NowPos = float4::LerpClamp(StartPos, EndPos, Ratio);
	SetPos(NowPos);

	if (Timer < OpenTime)
		return;

	RenderPtr->SetFrame(static_cast<int>(State::Open));
	NowState = State::Open;
}

void BossDeadBox::Update_Open(float _DeltaTime)
{
	const size_t MaxCreateCnt = 15;
	static size_t CreatedCnt = 0;

	const float ItemSpawnTime = 0.2f;
	static float Timer = 0.f;

	Timer += _DeltaTime;
	if (Timer < ItemSpawnTime)
		return;
	
	//아이템 생성
	Item_GravityNormal* Item = GetLevel()->CreateActor<Item_GravityNormal>(UpdateOrder::Item);
	Item->SetPos(GetPos() + ItemOffset);
	++CreatedCnt;
	Timer -= ItemSpawnTime;

	if (CreatedCnt < MaxCreateCnt)
		return;

	Item_BossJewellery* Jewellry = GetLevel()->CreateActor<Item_BossJewellery>(UpdateOrder::Item);
	Jewellry->SetPos(GetPos() + ItemOffset);
	CreatedCnt = 0;
	Death();
}
