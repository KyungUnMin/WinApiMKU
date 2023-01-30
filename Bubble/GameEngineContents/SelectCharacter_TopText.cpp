#include "SelectCharacter_TopText.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "SelectCharacterLevel.h"

//Player Select 텍스트의 오프셋 값
const float SelectCharacter_TopText::BubbleOffset[12] =
{
	-6.f, -5.f,-4.f,-3.f,-2.f,-1.f,
	1.f,2.f,3.f,4.f,5.f,6.f
};

SelectCharacter_TopText::SelectCharacter_TopText()
{

}

SelectCharacter_TopText::~SelectCharacter_TopText()
{

}



void SelectCharacter_TopText::Start()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	SetPos({ScreenSize.x / 2.f, 140.f});

	int CutIndex = 3;
	for (size_t i = 0; i < 12; ++i)
	{
		//PlayerSelect 글자 이미지
		GameEngineRender* TextRender = CreateRender("SelectCharacter_PlayerSelectText.bmp", SelectCharacterRenderOrder::UI);
		TextRender->SetFrame(static_cast<int>(i));
		TextRender->SetScale({ 64.f, 64.f });
		TextRender->SetPosition(float4::Right * BubbleOffset[i] * 64.f);

		//PlayerSelect 글자 뒤 Bubble 이미지
		GameEngineRender* BubbleRender = CreateRender("SelectCharacter_Bubble.bmp", SelectCharacterRenderOrder::Bubble);
		BubbleRender->SetFrame(CutIndex);
		CutIndex = (CutIndex + 1) % 6;
		BubbleRender->SetScale({ 85.f, 85.f });
		BubbleRender->SetPosition(float4::Right * BubbleOffset[i] * 64.f);
	}
	
	//Time 글자 이미지
	const float OffsetX[4] = {-150.f, -120.f, -90.f, -50.f};
	for (size_t i = 0; i < 4; ++i)
	{
		GameEngineRender* TimeTextRender = CreateRender("SelectCharacter_TimeText.bmp", SelectCharacterRenderOrder::UI);
		TimeTextRender->SetFrame(static_cast<int>(i));
		TimeTextRender->SetPosition({OffsetX[i], 100.f});
		TimeTextRender->SetScale({ 160.f, 192.f });
	}

	//타이머 숫자
	NumberRender = CreateRender("SelectCharacter_Numbers.bmp", SelectCharacterRenderOrder::UI);
	NumberRender->SetFrame(NumberFrameIndex);
	NumberRender->SetPosition({ 50.f, 100.f });
	NumberRender->SetScale({ 160.f, 192.f });
}

void SelectCharacter_TopText::Update(float _DeltaTime)
{
	AccTime += _DeltaTime;

	//1초가 지날때마다
	if (AccTime < 1.f)
		return;

	AccTime -= 1.f;

	//타이머 숫자 감소
	if ((0 < NumberFrameIndex) && false == SelectCharacterLevel::Selected)
	{
		--NumberFrameIndex;
		NumberRender->SetFrame(NumberFrameIndex);
	}

	//타이머 시간이 전부 끝났거나 외부에서 캐릭터를 이미 선택했을때
	else
	{
		SelectCharacterLevel::Selected = true;
	}
}


//타이머 초기화
void SelectCharacter_TopText::Reset()
{
	AccTime = 0.f;
	NumberFrameIndex = 9;
	NumberRender->SetFrame(NumberFrameIndex);
}
