#include "BubbleCore.h"
#include <GameEnginePlatform/GameEngineInput.h>
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

//ΩÃ±€≈Ê ∞¥√º
BubbleCore BubbleCore::Core;

BubbleCore::BubbleCore()
{

}

BubbleCore::~BubbleCore()
{

}



void BubbleCore::Start()
{
	int* FOR_DEBUG = new int;

	CreateLevels();
	CreateKeys();
}

void BubbleCore::CreateLevels()
{
	//≈∏¿Ã∆≤
	CreateLevel<OpeningLevel>("OpeningLevel");
	CreateLevel<SelectPlayerLevel>("SelectPlayerLevel");
	CreateLevel<SelectCharacterLevel>("SelectCharacterLevel");
	CreateLevel<EnterRoundLevel>("EnterRoundLevel");

	//RoundA
	CreateLevel<RoundAEnterLevel>("RoundAEnterLevel");
	CreateLevel<RoundA1Level>("RoundA1Level");
	CreateLevel<RoundA2Level>("RoundA2Level");
	CreateLevel<RoundA3Level>("RoundA3Level");

	//ø£µ˘»≠∏È
	CreateLevel<EndingLevel>("EndingLevel");

	ChangeLevel("OpeningLevel");
}


void BubbleCore::CreateKeys()
{
	GameEngineInput::CreateKey(DEBUG_RENDER, VK_F1);
	GameEngineInput::CreateKey(CHEET_STAGE_CLEAR, VK_F2);

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
	}

}

void BubbleCore::End()
{
	
}


