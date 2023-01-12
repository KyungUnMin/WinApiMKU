#include "Stage01.h"
#include "Player.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

Stage01::Stage01()
{

}

Stage01::~Stage01()
{

}

void Stage01::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("aaaaa.BmP"));
	Image->Cut(4, 8);


	CreateActor<Player>();
}

void Stage01::Update()
{
}
