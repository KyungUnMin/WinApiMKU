#include "BubbleCore.h"

#include "OpeningLevel.h"
#include "SelectPlayerLevel.h"
#include "SelectCharacterLevel.h"
#include "EnterRoundLevel.h"

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


	CreateLevel<OpeningLevel>("OpeningLevel");
	CreateLevel<SelectPlayerLevel>("SelectPlayerLevel");
	CreateLevel<SelectCharacterLevel>("SelectCharacterLevel");
	CreateLevel<EnterRoundLevel>("EnterRoundLevel");

	ChangeLevel("OpeningLevel");
}

void BubbleCore::Update()
{

}

void BubbleCore::End()
{
	
}


