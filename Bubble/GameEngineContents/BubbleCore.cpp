#include "BubbleCore.h"

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

	ChangeLevel("RoundAEnterLevel");
}

void BubbleCore::Update()
{

}

void BubbleCore::End()
{
	
}


