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

//싱글톤 객체
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
	//타이틀
	CreateLevel<OpeningLevel>("OpeningLevel");
	CreateLevel<SelectPlayerLevel>("SelectPlayerLevel");
	CreateLevel<SelectCharacterLevel>("SelectCharacterLevel");
	CreateLevel<EnterRoundLevel>("EnterRoundLevel");

	//RoundA
	CreateLevel<RoundAEnterLevel>("RoundAEnterLevel");
	CreateLevel<RoundA1Level>("RoundA1Level");
	CreateLevel<RoundA2Level>("RoundA2Level");
	CreateLevel<RoundA3Level>("RoundA3Level");

	//엔딩화면
	CreateLevel<EndingLevel>("EndingLevel");

	ChangeLevel("RoundA2Level");
}


void BubbleCore::CreateKeys()
{
	GameEngineInput::CreateKey(DEBUG_RENDER, VK_F1);
	GameEngineInput::CreateKey("PlayerUnbeatableSwitch", VK_F2);

	GameEngineInput::CreateKey("GridSwitch", VK_F3);
	GameEngineInput::CreateKey(CHEET_STAGE_CLEAR, VK_F5);

	GameEngineInput::CreateKey(PLAYER_LEFT, KEY_LEFT);
	GameEngineInput::CreateKey(PLAYER_RIGHT, KEY_RIGHT);
	GameEngineInput::CreateKey(PLAYER_JUMP, KEY_JUMP);
	GameEngineInput::CreateKey(PLAYER_ATTACK, KEY_ATTACK);
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

	//플레이어 무적모드 스위치
	if (true == GameEngineInput::IsDown("PlayerUnbeatableSwitch"))
	{
		PlayerBase::UnbeatableSwitch();
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


