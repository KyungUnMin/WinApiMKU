#include "BubbleCore.h"
#include "TitleLevel.h"
#include "Stage01.h"

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

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<Stage01>("State01");

	ChangeLevel("State01");
}

void BubbleCore::Update()
{

}

void BubbleCore::End()
{
	
}


