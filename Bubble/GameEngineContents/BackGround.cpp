#include "BackGround.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>

BackGround::BackGround()
{
	
}

BackGround::~BackGround()
{
	if (Image)
		Image = nullptr;
	/*
	if (UpdateCallBack)
		UpdateCallBack = nullptr;

	if (CurrentLevel)
		CurrentLevel = nullptr;*/
}

void BackGround::Start()
{
	SetPos(GameEngineWindow::GetScreenSize().half());
	Image = GameEngineResources::GetInst().ImageFind("BackGround.bmp");
}

void BackGround::ImageFind(const std::string_view& _ImageKey)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageKey);
}

//void BackGround::Update()
//{
//	if (nullptr != UpdateCallBack && nullptr != CurrentLevel)
//	{
//		(CurrentLevel->*UpdateCallBack)();
//	}
//}

void BackGround::Render()
{
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, GetPos(), GameEngineWindow::GetScreenSize(), float4::Zero, Image->GetImageScale());
}


