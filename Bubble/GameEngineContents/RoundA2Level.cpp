#include "RoundA2Level.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleCore.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "PlayerBase.h"

RoundA2Level::RoundA2Level()
{

}

RoundA2Level::~RoundA2Level()
{

}



void RoundA2Level::Loading()
{
	//�÷��̾ ������ ��ġ ����
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	SetPlayerSpawnPos({ ScreenSize.x * 0.2f,  ScreenSize.y * 0.8f });

	//���ҽ� �ε�
	ResourceLoad();
	RoundLevelBase::LoadObstacle("A2", 6, 1);

	//��� �� ������ ������ ���������� �����Ͽ� ����
	CreateBackGround();
	RoundLevelBase::CreateObstacle(float4::Right, RoundRenderOrder::Obstacle1);

	//ġƮŰ
	GameEngineInput::CreateKey("A2_NextStage", VK_F1);
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
	GameEngineRender* Render1 = Back->CreateRender("RoundA2_BackGround1.bmp", RoundRenderOrder::BackGround1);
	Render1->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "RoundA2_BackGround1.bmp",
		.Start = 0,
		.End = 6,
		.InterTimer = 0.15f,
	});
	Render1->ChangeAnimation("Idle");

	GameEngineRender* Render2 = Back->CreateRender("RoundA2_BackGround2.bmp", RoundRenderOrder::BackGround2);
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


void RoundA2Level::Update(float _DeltaTime)
{
	//RoundLevelBase::MoveToNextStage�� ȣ��Ǿ��ٸ� Stage�� ��ĭ �̵���Ų��
	//���� ȣ����� �ʾҴٸ� �׶��� �������� �ʴ´�
	RoundLevelBase::Update(_DeltaTime);

	//ġƮŰ�� �����°�?
	if (false == GameEngineInput::IsDown("A2_NextStage"))
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

void RoundA2Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//�÷��̾� ����
	RoundLevelBase::LevelChangeStart(_PrevLevel);
	GetPlayer()->SetPos(GetPlayerSpawnPos());
}

