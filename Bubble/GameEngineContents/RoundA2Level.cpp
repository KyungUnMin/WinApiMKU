#include "RoundA2Level.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "ContentsDefine.h"
#include "PlayerBase.h"
#include "BubbleDestHelper.h"


RoundA2Level::RoundA2Level()
{

}

RoundA2Level::~RoundA2Level()
{

}



void RoundA2Level::Loading()
{
	RoundLevelBase::Loading();

	//���ҽ� �ε�
	ResourceLoad();
	RoundLevelBase::LoadStage("A2", 6, 1);

	//��� �� ������ ������ ���������� �����Ͽ� ����
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);


	CreateBubbleDest();
}


void RoundA2Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA2");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA2_BackGround1.bmp"))->Cut(4, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA2_BackGround2.bmp"))->Cut(2, 1);
}

//2���� ��� �ִϸ��̼�
void RoundA2Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	GameEngineRender* Render1 = Back->CreateRender("RoundA2_BackGround1.bmp", RenderOrder::BackGround1);
	Render1->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA2_BackGround1.bmp",
		.Start = 0,
		.End = 6,
		.InterTimer = 0.15f,
	});
	Render1->ChangeAnimation("Idle");

	GameEngineRender* Render2 = Back->CreateRender("RoundA2_BackGround2.bmp", RenderOrder::BackGround2);
	Render2->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA2_BackGround2.bmp",
		.Start = 0,
		.End = 1,
		.InterTimer = 0.25f,
	});
	Render2->ChangeAnimation("Idle");
}

void RoundA2Level::CreateBubbleDest()
{
	GetBubbleDestHelper()->SetBubbleDest(HelpLevelType::RoundA2);

	{
		size_t Stage = 0;
		for (size_t i = 0; i < 2; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
		
		for (size_t i = 3; i < 5; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 1;
		for (size_t i = 0; i < 5; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 6; i < 11; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 12; i < 15; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

	}

	{
		size_t Stage = 2;
		for (size_t i = 0; i < 7; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 8; i < 15; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

	}

	{
		size_t Stage = 3;
		for (size_t i = 0; i < 4; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 5; i < 9; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		GetBubbleDestHelper()->ConnectDestToDest(Stage, 10, 1);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 11, 6);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 12, 3);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 13, 8);
	}

	{
		size_t Stage = 4;
		for (size_t i = 0; i < 5; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 6; i < 11; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 12; i < 15; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 5;
		for (size_t i = 0; i < 11; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 12; i < 14; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 14, 4);

		for (size_t i = 15; i < 17; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 17, 5);

		for (size_t i = 18; i < 20; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 20, 6);
	}

}


void RoundA2Level::Update(float _DeltaTime)
{
	//RoundLevelBase::MoveToNextStage�� ȣ��Ǿ��ٸ� Stage�� ��ĭ �̵���Ų��
	//���� ȣ����� �ʾҴٸ� �׶��� �������� �ʴ´�
	RoundLevelBase::Update(_DeltaTime);

	//ġƮŰ�� �����°�?
	if (false == GameEngineInput::IsDown(CHEET_STAGE_CLEAR))
		return;

	//�������� �̵����ΰ�?
	if (true == RoundLevelBase::MoveToNextStage())
		return;

	//�� Stage�� �̹� Round�� ������ Stage�ΰ�?
	if (false == RoundLevelBase::IsLastStage())
		return;

	//���������� ��ȯ
	BubbleCore::GetInst().ChangeLevel("EndingLevel");
}


