#include "RoundA_Enter_BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsEnum.h"

RoundA_Enter_BackGround::RoundA_Enter_BackGround()
{

}

RoundA_Enter_BackGround::~RoundA_Enter_BackGround()
{

}

void RoundA_Enter_BackGround::Start()
{
	BackGrounds.resize(4, nullptr);
	for (size_t i = 0; i < BackGrounds.size(); ++i)
	{
		BackGrounds[i] = CreateRender("Enter.bmp", RenderOrder::BackGround);
		BackGrounds[i]->SetPosition(GameEngineWindow::GetScreenSize().half());
		BackGrounds[i]->SetScale(GameEngineWindow::GetScreenSize() * 1.04f);
		BackGrounds[i]->SetFrame(ImageIndex[i]);
	}
	
	BackGrounds[1]->SetPosition(BackGrounds[1]->GetPosition() + float4::Right * GameEngineWindow::GetScreenSize());
}

void RoundA_Enter_BackGround::Update(float _DeltaTime)
{
	for (size_t i = 0; i < 2; ++i)
	{
		float4 Pos = BackGrounds[i]->GetPosition();
		Pos += MoveDir * SkyMoveSpeed * _DeltaTime;
		BackGrounds[i]->SetPosition(Pos);
	}

	DirTime += _DeltaTime;
	if (DirTime < DirChangeTime)
		return;

	DirTime -= DirChangeTime;
	MoveDir *= float4::Left;
}
