#include "BubbleCore.h"
#include "TitleLevel.h"
#include "SelectPlayerLevel.h"
#include "RoundA_Enter.h"

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

	//CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<SelectPlayerLevel>("SelectPlayerLevel");
	CreateLevel<RoundA_Enter>("RoundA_Enter");

	ChangeLevel("SelectPlayerLevel");
}

void BubbleCore::Update()
{

}

void BubbleCore::End()
{
	
}


