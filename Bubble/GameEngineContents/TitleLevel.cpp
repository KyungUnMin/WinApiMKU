#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BackGround.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Opening");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BackGround.bmp"));




	CreateActor<BackGround>();
}

void TitleLevel::Update()
{

}
