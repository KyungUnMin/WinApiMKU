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

const std::vector<float4> RoundA1Level::PlayerSpanwPos = 
{
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f },
	{ 100.f, 700.f }
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


