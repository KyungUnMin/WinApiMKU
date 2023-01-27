#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "TextLine.h"
#include "BubbleCore.h"

EndingLevel::EndingLevel()
{

}

EndingLevel::~EndingLevel()
{

}

void EndingLevel::Loading()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	TextLine* Text = CreateActor<TextLine>();
	Text->SetPos(ScreenSize.half());
	Text->SetScale({30.f, 50.f});
	Text->SetString("Thank You For Playing", TextLineColor::Gold);

	Text = CreateActor<TextLine>();
	Text->SetPos(ScreenSize.half() + float4::Down * 100.f);
	Text->SetScale({ 20.f, 30.f });
	Text->SetString("Press \'R\' For Restart", TextLineColor::Red);

	GameEngineInput::CreateKey("ReStart", 'R');
}

void EndingLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ReStart"))
		BubbleCore::GetInst().ChangeLevel("SelectCharacterLevel");
}
