#include "PointEffect.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"
#include "PointPannel.h"

const std::string_view	PointEffect::ImagePath = "PointEffect.bmp";
const std::vector<int>		PointEffect::ImageScores = 
{
	10,20,30,40,50,60,70,80,90,100,
	150,200,250,300,350,400,450,500,550,600,
	650,700,750,800,850,900,950,100,1200,2000,
	3000,4000,5000,6000,7000,8000,9000
};

PointEffect::PointEffect()
{

}

PointEffect::~PointEffect()
{

}

void PointEffect::Start()
{
	ResourceLoad();
	SelectImageFrame();
}



void PointEffect::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(10, 4);
	IsLoad = true;
}

void PointEffect::SelectImageFrame()
{
	int SelectFrame = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(ImageScores.size() - 1));

	RenderPtr = CreateRender(ImagePath, RenderOrder::UI);
	RenderPtr->SetFrame(SelectFrame);

	int Score = ImageScores[SelectFrame];
	PointPannel::AddPoint(Score);
}



void PointEffect::Update(float _DeltaTime)
{
	if (AliveTime < GetLiveTime())
	{
		Death();
		return;
	}

	RenderPtr->SetMove(float4::Up * MoveSpeed * _DeltaTime);
	Update_Scale();
}

void PointEffect::Update_Scale()
{
	const float UntilGrowTime = 0.2f;
	const float UntilDiminishTime = 0.2f;

	float LiveTime = GetLiveTime();
	if (LiveTime < UntilGrowTime)
	{
		float Ratio = (LiveTime / UntilGrowTime);
		float4 NowSize = float4::LerpClamp(float4::Zero, MaxSize, Ratio);
		RenderPtr->SetScale(NowSize);
		return;
	}

	float DiminishTime = (AliveTime - UntilDiminishTime);
	if (LiveTime < DiminishTime)
	{
		RenderPtr->SetScale(MaxSize);
		return;
	}

	if (DiminishTime < LiveTime)
	{
		float Ratio = ((LiveTime - DiminishTime) / (AliveTime - DiminishTime));
		float4 NowSize = float4::LerpClamp(MaxSize, float4::Zero, Ratio);
		RenderPtr->SetScale(NowSize);
		return;
	}
}