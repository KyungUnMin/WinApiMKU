#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "TextLine.h"
#include "BubbleCore.h"

EndingLevel::EndingLevel()
{
	BackColor = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
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
	Text->SetString("Press \'R\' To Restart", TextLineColor::Red);

	GameEngineInput::CreateKey("ReStart", 'R');
}

void EndingLevel::Update(float _DeltaTime)
{
	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	BackColor = static_cast<HBRUSH>(SelectObject(Hdc, BackColor));
	Rectangle(Hdc, -1, -1, ScreenSize.ix() + 1, ScreenSize.iy() + 1);
	BackColor = static_cast<HBRUSH>(SelectObject(Hdc, BackColor));


	if (true == GameEngineInput::IsDown("ReStart"))
		BubbleCore::GetInst().ChangeLevel("SelectCharacterLevel");
}
