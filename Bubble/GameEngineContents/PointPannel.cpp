#include "PointPannel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "RoundLevelBase.h"
#include "ContentsEnum.h"
#include "TextLine.h"

PointPannel::PointPannel()
{

}

PointPannel::~PointPannel()
{

}

void PointPannel::Start()
{
	ResourceLoad();
	CreatePannel();
	CreateText();
}

void PointPannel::Update(float _DeltaTime)
{
	


}

void PointPannel::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PointPannel.bmp"));

	IsLoad = true;
}

void PointPannel::CreatePannel()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	SetPos({ ScreenSize.hx(), OffsetY * 0.5f });
	RenderPtr = CreateRender("PointPannel.bmp", RenderOrder::UI);
	RenderPtr->SetScale({ ScreenSize.x, OffsetY });
}

void PointPannel::CreateText()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	TextLine* T1 = GetLevel()->CreateActor<TextLine>();
	T1->SetAlign(TextAlignType::Right);
	T1->SetScale({ 30.f ,50.f });
	T1->SetPos({ ScreenSize.x, 50.f });
	T1->SetString("Hello Welcome to My TExt", TextLineColor::White);
}
