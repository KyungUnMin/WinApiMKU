#include "RoundA_Enter.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include "RoundA_Enter_BackGround.h"

RoundA_Enter::RoundA_Enter()
{

}

RoundA_Enter::~RoundA_Enter()
{

}

void RoundA_Enter::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");

	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Enter.bmp"));
	Image->Cut(4, 2);

	CreateActor<RoundA_Enter_BackGround>();
}

void RoundA_Enter::Update(float _DeltaTime)
{

}

void RoundA_Enter::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void RoundA_Enter::LevelChangeStart(GameEngineLevel* _NextLevel)
{

}
