#include "RoundA1Level.h"
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
#include "BubbleDestination.h"

const std::vector<float4> RoundA1Level::PlayerSpanwPos = 
{
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f }
};

const std::vector<std::vector<float4>> RoundA1Level::BubbleDestPos =
{
	{{100.f, 600.f},{100.f, 200.f},{860.f, 600.f},{860.f, 200.f},{480.f, 200.f}, {480.f, 100.f},{480.f, 600.f}, {480.f, 300.f}, {100.f, 400.f}, {860.f, 400.f}},

	{{350.f, 650.f},{100.f, 650},{100.f, 500.f},{100.f, 150.f},
		{610.f, 650}, {860.f, 650},{860.f, 500.f}, {860.f, 150.f},
			{480.f, 150.f}, {480.f, 250.f}, {480.f, 400.f}},

	{{650.f, 100.f},{350.f, 100.f},{100.f, 100.f},
		{100.f, 250.f},{350.f, 250.f},{650.f, 250.f},{860.f, 250.f},
			{860.f, 400.f},{650.f, 400.f},{350.f, 400.f},{100.f, 400.f},
				{100.f, 520.f},{350.f, 520.f},{650.f, 520.f},{860.f, 520.f},
					{860.f, 650.f},{650.f, 650.f},{350.f, 650.f},{100.f, 650.f},
												{350.f, 800.f},{650.f, 800.f}},

	{{100.f, 600.f},{100.f, 100.f},{480.f, 100.f}, {860.f, 100.f},{860.f, 600.f}},
	{{100.f, 600.f},{100.f, 100.f},{480.f, 100.f}, {860.f, 100.f},{860.f, 600.f}},
	{{100.f, 600.f},{100.f, 100.f},{480.f, 100.f}, {860.f, 100.f},{860.f, 600.f}},
};

RoundA1Level::RoundA1Level()
{

}

RoundA1Level::~RoundA1Level()
{

}

void RoundA1Level::Loading()
{
	//���ҽ� �ε�
	ResourceLoad();
	RoundLevelBase::LoadStage("A1", 6, 1);

	//�� ���� ������ ������ �Ʒ��� �����Ͽ� ����
	CreateBackGround();
	RoundLevelBase::CreateStage(float4::Down, RenderOrder::Obstacle1);

	//�÷��̾ ������ ��ġ ����
	SetPlayerSpawnPos(PlayerSpanwPos);

	CreateBubbleDest();
}

void RoundA1Level::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("RoundA");
	Dir.Move("RoundA1");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA1_BackGround.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RoundA1_BackEffect.bmp"))->Cut(3, 1);
}


//2���� ��� �ִϸ��̼� ����
void RoundA1Level::CreateBackGround()
{
	BackGround* Back = CreateActor<BackGround>();
	Back->RenderReserve(2);
	Back->CreateRender("RoundA1_BackGround.bmp", RenderOrder::BackGround1);

	GameEngineRender* Effect = Back->CreateRender("RoundA1_BackEffect.bmp", RenderOrder::BackGround2);
	Effect->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA1_BackEffect.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.15f
	});

	Effect->ChangeAnimation("Idle");
}

void RoundA1Level::CreateBubbleDest()
{
	SetBubbleDest(BubbleDestPos);

	{
		size_t Stage = 0;
		ConnectDestToDest(Stage, 0, 1);
		ConnectDestToDest(Stage, 1, 4);
		ConnectDestToDest(Stage, 2, 3);
		ConnectDestToDest(Stage, 3, 4);
		ConnectDestToDest(Stage, 4, 5);
		ConnectDestToDest(Stage, 6, 7);
		ConnectDestToDest(Stage, 8, 1);
		ConnectDestToDest(Stage, 9, 3);
	}
	
	{
		size_t Stage = 1;
		ConnectDestToDest(Stage, 0, 1);
		ConnectDestToDest(Stage, 1, 3);
		ConnectDestToDest(Stage, 2, 3);
		ConnectDestToDest(Stage, 4, 5);
		ConnectDestToDest(Stage, 5, 7);
		ConnectDestToDest(Stage, 6, 7);
		ConnectDestToDest(Stage, 3, 8);
		ConnectDestToDest(Stage, 7, 8);
		ConnectDestToDest(Stage, 8, 9);
		ConnectDestToDest(Stage, 10, 9);
	}
	
	{
		size_t Stage = 2;
		for (size_t i = 0; i < 15; ++i)
		{
			ConnectDestToDest(Stage, i, i + 1);
		}

		ConnectDestToDest(Stage, 15, 16);
		ConnectDestToDest(Stage, 18, 17);
		ConnectDestToDest(Stage, 17, 19);
		ConnectDestToDest(Stage, 16, 20);
	}
	
}


void RoundA1Level::Update(float _DeltaTime)
{
	//RoundLevelBase::MoveToNextStage�� ȣ��Ǿ��ٸ� Stage�� ��ĭ �̵���Ų��
	//���� ȣ����� �ʾҴٸ� �׶��� �������� �ʴ´�
	RoundLevelBase::Update(_DeltaTime);
	
	//ġƮŰ �����°�?
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


