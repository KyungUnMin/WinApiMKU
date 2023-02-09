#include "RoundA3Level.h"
#include <vector>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "ContentsDefine.h"
#include "PlayerBase.h"
#include "BubbleDestHelper.h"

const std::vector<float4> RoundA3Level::PlayerSpanwPos = 
{
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f }
};

RoundA3Level::RoundA3Level()
{

}

RoundA3Level::~RoundA3Level()
{

}

void RoundA3Level::Loading()
{
	RoundLevelBase::Loading();

	//���ҽ� �ε�
	ResourceLoad();
	RoundLevelBase::LoadStage("A3", 6, 1);

	//�� ���� ������ ������ ���������� �����Ͽ� ����
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Right, RenderOrder::Obstacle1);

	//�÷��̾ ������ ��ġ ����
	SetPlayerSpawnPos(PlayerSpanwPos);

	CreateBubbleDest();
}



void RoundA3Level::Update(float _DeltaTime)
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





void RoundA3Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA3");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA3_BackGround1.bmp"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA3_BackGround2.bmp"))->Cut(3, 1);
}


//2���� ��� �ִϸ��̼�
void RoundA3Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->RenderReserve(2);

	GameEngineRender* Render1 = Back->CreateRender("RoundA3_BackGround1.bmp", RenderOrder::BackGround1);

	Render1->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA3_BackGround1.bmp",
		.InterTimer = 0.2f,
		.FrameIndex = std::vector<int> { 0, 1, 2, 3, 4, 3 },
	});
	Render1->ChangeAnimation("Idle");

	GameEngineRender* Render2 = Back->CreateRender("RoundA3_BackGround2.bmp", RenderOrder::BackGround2);
	Render2->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA3_BackGround2.bmp",
		.InterTimer = 0.2f,
		.FrameIndex = std::vector<int> { 0, 1, 2, 1 }
	});
	Render2->ChangeAnimation("Idle");
}

void RoundA3Level::CreateBubbleDest()
{
	GetBubbleDestHelper()->SetBubbleDest(HelpLevelType::RoundA3);

	{
		size_t Stage = 0;
		for (size_t i = 0; i < 4; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i,i + 1);
		}
	}

	{
		size_t Stage = 1;
		for (size_t i = 0; i < 6; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i+1);
		}
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 6, 3);

		for (size_t i = 7; i < 10; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 10, 4);
		

		GetBubbleDestHelper()->ConnectDestToDest(Stage, 11, 6);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 12, 5);
	}

	{
		size_t Stage = 2;
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 0, 1);
		GetBubbleDestHelper()->ConnectDestToDest(Stage, 2, 3);

		for (size_t i = 4; i < 7; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 8; i < 11; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 3;
		for (size_t i = 0; i < 6; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 7; i < 13; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 14; i < 17; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 4;
		for (size_t i = 0; i < 9; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}
	}

	{
		size_t Stage = 5;
		for (size_t i = 0; i < 7; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 8; i < 13; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

		for (size_t i = 14; i < 21; ++i)
		{
			GetBubbleDestHelper()->ConnectDestToDest(Stage, i, i + 1);
		}

	}
}

