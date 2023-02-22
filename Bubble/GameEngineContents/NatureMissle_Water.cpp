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



//BubbleStatePop���� ȣ���
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

	//�̹��� ������ ����
	SetImageFrame();

	//if (nullptr == FrontWater)
	//{
		//�� ���� �ĵ� �̵�
		HeadMove(_DeltaTime);
	//}
	//else
	//{
	//	//�� �� �ĵ��� ������ ������ �ĵ� �̵�
	//	TailMove(_DeltaTime);
	//}

}


void NatureMissle_Water::HeadMove(float _DeltaTime)
{
	//���� ��带 ���� �����̱� ������ ��ġ�� ����
	PrevPos = GetPos();

	//���߿� �ִٸ� �Ʒ��� �̵�
	if (false == IsGround(NatureMissleBase::CollisionScale))
	{
		//�Ʒ��� �̵�
		SetMove(float4::Down * MoveSpeed * _DeltaTime);

		//ĳ���Ͱ� ȭ�� �Ʒ��� �������ٸ� ���� �ø���
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 NowPos = GetPos();
		if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
		{
			//if(10.f <  GetLiveTime())
				//Death();

			//y�� 0���� �����
			SetPos(NowPos * float4::Right);
		}
	}

	//�׷��� �ʴٸ� �������� �̵�
	else
	{
		RaiseOnGround(NatureMissleBase::CollisionScale);

		//�����̰� ���� �����ٸ� false�� return
		if (false == MoveHorizon(MoveSpeed.x, NatureMissleBase::CollisionScale, _DeltaTime))
		{
			//������ �ݴ�� ��ȯ
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


	//���߿� �ִٸ�
	if (false == IsGround(NatureMissleBase::CollisionScale))
	{
		GetRender()->SetFrame(FallFrmIndex);
		return;
	}

	//������ ���ʿ� ���� �ִϸ��̼�
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
