#include "NatureMissle_Water.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

const std::string_view				NatureMissle_Water::ImagePath	= "Water.bmp";
std::list<NatureMissle_Water*>	NatureMissle_Water::AllWaters;


NatureMissle_Water::NatureMissle_Water()
{

}

NatureMissle_Water::~NatureMissle_Water()
{
	
}



void NatureMissle_Water::Start()
{
	NatureMissleBase::Start();
	ResourceLoad();

	GetRender()->SetImage(ImagePath);
	GetRender()->SetFrame(0);
}



void NatureMissle_Water::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("NatureMissle");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImagePath))->Cut(5, 2);
	IsLoad = true;
}



//BubbleStatePop에서 호출됨
void NatureMissle_Water::InitPos(const float4& _HeadPos)
{
	StartPos = _HeadPos;

	if (true == AllWaters.empty())
	{
		PrevPos = _HeadPos;
		SetPos(_HeadPos);
	}
	else
	{
		FrontWater = AllWaters.back();
		PrevPos = FrontWater->GetPrevPos();
		SetPos(FrontWater->GetPrevPos());
	}

	AllWaters.push_back(this);
}



void NatureMissle_Water::Update(float _DeltaTime)
{
	if (0 != WaterCount && GetLiveTime() >= 0.1f)
	{
		NatureMissle_Water* WaterMissle = GetLevel()->CreateActor<NatureMissle_Water>(UpdateOrder::Nature_Missle);
		WaterMissle->SetWaterCount(--WaterCount);
		WaterMissle->InitPos(StartPos);
		WaterCount = 0;
	}

	//이미지 프레임 결정
	SetImageFrame();

	//if (nullptr == FrontWater)
	//{
		//맨 앞쪽 파도 이동
		HeadMove(_DeltaTime);
	//}
	//else
	//{
	//	//맨 앞 파도를 제외한 나머지 파도 이동
	//	TailMove(_DeltaTime);
	//}

}


void NatureMissle_Water::HeadMove(float _DeltaTime)
{
	//뒤쪽 노드를 위해 움직이기 이전의 위치값 저장
	PrevPos = GetPos();

	//공중에 있다면 아래로 이동
	if (false == IsGround(NatureMissleBase::CollisionScale))
	{
		//아래로 이동
		SetMove(float4::Down * MoveSpeed * _DeltaTime);

		//캐릭터가 화면 아래로 내려갔다면 위로 올리기
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 NowPos = GetPos();
		if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
		{
			//if(10.f <  GetLiveTime())
				//Death();

			//y를 0으로 만들기
			SetPos(NowPos * float4::Right);
		}
	}

	//그렇지 않다면 수평으로 이동
	else
	{
		RaiseOnGround(NatureMissleBase::CollisionScale);

		//움직이고 벽에 막혔다면 false를 return
		if (false == MoveHorizon(MoveSpeed.x, NatureMissleBase::CollisionScale, _DeltaTime))
		{
			//방향을 반대로 전환
			SetReverseDir();
		}
	}
}



void NatureMissle_Water::TailMove(float _DeltaTime)
{
	PrevPos = GetPos();
	SetPos(FrontWater->GetPrevPos());
}




void NatureMissle_Water::SetImageFrame()
{
	static const int FallFrmIndex = 7;
	static const int RightFrmIndex = 0;
	static const int LeftFrmIndex = 4;


	//공중에 있다면
	if (false == IsGround(NatureMissleBase::CollisionScale))
	{
		GetRender()->SetFrame(FallFrmIndex);
		return;
	}

	//오른쪽 왼쪽에 따른 애니메이션
	float4 Dir = GetDirVec();
	if (float4::Right == Dir)
	{
		GetRender()->SetFrame(RightFrmIndex);
	}
	else if (float4::Left == Dir)
	{
		GetRender()->SetFrame(LeftFrmIndex);
	}

}
