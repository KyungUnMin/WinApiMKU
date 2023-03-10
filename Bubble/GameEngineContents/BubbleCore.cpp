#include "BubbleCore.h"
#include <time.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "BubbleDestHelper.h"

#include "ContentsDefine.h"
#include "OpeningLevel.h"
#include "SelectPlayerLevel.h"
#include "SelectCharacterLevel.h"
#include "EnterRoundLevel.h"
#include "RoundAEnterLevel.h"
#include "RoundA1Level.h"
#include "RoundA2Level.h"
#include "RoundA3Level.h"
#include "EndingLevel.h"
#include "PlayerBase.h"

//?̱??? ??ü
BubbleCore BubbleCore::Core;

BubbleCore::BubbleCore()
{
	
}

BubbleCore::~BubbleCore()
{
	
}

void BubbleCore::Start()
{
	bool* FOR_DEBUG = new bool;
	srand(static_cast<unsigned int>(time(nullptr)));

	CreateDebugPenBrush();
	CreateLevels();
	CreateKeys();
}



void BubbleCore::CreateDebugPenBrush()
{
	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

	DebugPen = static_cast<HPEN>(CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
	DebugBrush = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));

	DebugPen = static_cast<HPEN>(SelectObject(Hdc, DebugPen));
	DebugBrush = static_cast<HBRUSH>(SelectObject(Hdc, DebugBrush));
}



void BubbleCore::CreateLevels()
{
	//Ÿ??Ʋ
	CreateLevel<OpeningLevel>("OpeningLevel");
	CreateLevel<SelectPlayerLevel>("SelectPlayerLevel");
	CreateLevel<SelectCharacterLevel>("SelectCharacterLevel");
	CreateLevel<EnterRoundLevel>("EnterRoundLevel");

	//RoundA
	CreateLevel<RoundAEnterLevel>("RoundAEnterLevel");
	CreateLevel<RoundA1Level>("RoundA1Level");
	CreateLevel<RoundA2Level>("RoundA2Level");
	CreateLevel<RoundA3Level>("RoundA3Level");

	//????ȭ??
	CreateLevel<EndingLevel>("EndingLevel");

	ChangeLevel("OpeningLevel");
}


void BubbleCore::CreateKeys()
{
	GameEngineInput::CreateKey(DEBUG_RENDER, VK_F1);
	GameEngineInput::CreateKey("PlayerUnbeatableSwitch", VK_F2);

	GameEngineInput::CreateKey("GridSwitch", VK_F3);
	GameEngineInput::CreateKey(CHEET_STAGE_CLEAR, VK_F4);

	GameEngineInput::CreateKey(PLAYER_LEFT, KEY_LEFT);
	GameEngineInput::CreateKey(PLAYER_RIGHT, KEY_RIGHT);
	GameEngineInput::CreateKey(PLAYER_JUMP, KEY_JUMP);
	GameEngineInput::CreateKey(PLAYER_ATTACK, KEY_ATTACK);

	GameEngineInput::CreateKey("BossPath", VK_F6);
	GameEngineInput::CreateKey("GhostOnOff", VK_F7);
}




void BubbleCore::Update()
{
	if (true == GameEngineInput::IsDown(DEBUG_RENDER))
	{
		GameEngineLevel::DebugRenderSwitch();
		DebugSwitch();
	}

	if (true == GameEngineInput::IsDown("GridSwitch"))
	{
		BubbleDestHelper::RenderOnOffSwitch();
	}

	if (true == GameEngineInput::IsDown("BossPath"))
	{
		BossCheekOn = !BossCheekOn;
	}

	//?÷??̾? ???????? ????ġ
	if (true == GameEngineInput::IsDown("PlayerUnbeatableSwitch"))
	{
		PlayerBase::UnbeatableSwitch();
	}

	if (true == GameEngineInput::IsDown("GhostOnOff"))
	{
		GhostWork = !GhostWork;
	}

	if (false == GhostWork)
	{
		GameEngineLevel::DebugTextPush("???? ??Ȱ??ȭ");
	}
}

void BubbleCore::End()
{
	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	DebugPen = static_cast<HPEN>(SelectObject(Hdc, DebugPen));
	DebugBrush = static_cast<HBRUSH>(SelectObject(Hdc, DebugBrush));

	DeleteObject(DebugPen);
	DeleteObject(DebugBrush);
}


