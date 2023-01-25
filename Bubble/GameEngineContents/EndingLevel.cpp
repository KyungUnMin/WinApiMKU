#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "TextLine.h"

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
}
