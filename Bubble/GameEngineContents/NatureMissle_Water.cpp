#include "NatureMissle_Water.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "MonsterBase.h"
#include "PlayerBase.h"
#include "PlayerFSM.h"

const std::string_view		NatureMissle_Water::ImagePath			= "Water.bmp";
const float4						NatureMissle_Water::MoveColScale		= float4{ 5.f, 5.f };

size_t									NatureMissle_Water::AllCount = 0;
GameEngineSoundPlayer	NatureMissle_Water::WaterWave;


NatureMissle_Water::NatureMissle_Water()
{
}

NatureMissle_Water::~NatureMissle_Water()
{
	DragMonsters.clear();
	--AllCount;

	if (0 == AllCount)
	{
		WaterWave.Stop();
	}
}



void NatureMissle_Water::Start()
{
	NatureMissleBase::Start();
	LoadSFX();
	ResourceLoad();
	GetCollision()->SetScale(CollisionScale);


	GetRender()->SetImage(ImagePath);
	GetRender()->SetFrame(0);

	if (0 == AllCount)
	{
		WaterWave = GameEngineResources::GetInst().SoundPlayerToControl("WaterWave.wav");
	}
	++AllCount;
}



void NatureMissle_Water::LoadSFX()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Nature");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("WaterWave.wav"));
	IsLoad = true;
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




void NatureMissle_Water::Update(float _DeltaTime)
{
	CreateChild();

	//�̹��� ������ ����
	SetImageFrame();
	Move(_DeltaTime);

	MonsterKill();
	MonsterDrag();
	PlayerDrag();
}



void NatureMissle_Water::CreateChild()
{
	if (WaterCount <= 0)
		return;

	if (GetLiveTime() < CreateChildTime)
		return;

	NatureMissle_Water* WaterMissle = GetLevel()->CreateActor<NatureMissle_Water>(UpdateOrder::Nature_Missle);
	WaterMissle->SetCreateCount(WaterCount - 1, false);
	WaterMissle->InitPos(StartPos, StartDir);
	WaterCount = 0;
}






void NatureMissle_Water::SetImageFrame()
{
	static const int FallFrmIndex = 7;
	static const int RightFrmIndex = 4;
	static const int MidFrmIndex = 2;
	static const int LeftFrmIndex = 0;

	//���߿� �ִٸ�
	if (false == IsGround(NatureMissleBase::CollisionScale))
	{
		GetRender()->SetFrame(FallFrmIndex);
		return;
	}

	if (false == IsFirst)
	{
		GetRender()->SetFrame(MidFrmIndex);
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





void NatureMissle_Water::Move(float _DeltaTime)
{
	//���߿� �ִٸ� �Ʒ��� �̵�
	if (false == IsGround(MoveColScale))
	{
		//�Ʒ��� �̵�
		SetMove(float4::Down * MoveSpeed * _DeltaTime);

		//ȭ�� �Ʒ��� �������ٸ� ���ֱ�
		float4 ScreenSize = GameEngineWindow::GetScreenSize();
		float4 NowPos = GetPos();
		if (ScreenSize.y + ScreenOutOffsetY < NowPos.y)
		{
			//if(10.f <  GetLiveTime())
			Death();

			//y�� 0���� �����
			//SetPos(NowPos * float4::Right);
		}
	}

	//�׷��� �ʴٸ� �������� �̵�
	else
	{
		RaiseOnGround(MoveColScale);

		//�����̰� ���� �����ٸ� false�� return
		if (false == MoveHorizon(MoveSpeed.x, MoveColScale, _DeltaTime))
		{
			//������ �ݴ�� ��ȯ
			SetReverseDir();
		}
	}
}




void NatureMissle_Water::MonsterKill()
{
	static std::vector<MonsterBase*> CollisionMonsters;
	if (false == CollisionCheckWithMonster(CollisionMonsters))
		return;
	
	for (MonsterBase* Monster : CollisionMonsters)
	{
		Monster->DeathFromNature(this);
		DragMonsters.push_back(Monster);
	}
}

void NatureMissle_Water::MonsterDrag()
{
	auto Iter = DragMonsters.begin();
	while (Iter != DragMonsters.end())
	{
		if (false == (*Iter)->IsUpdate())
		{
			Iter = DragMonsters.erase(Iter);
			continue;
		}

		(*Iter)->SetPos(GetPos() + MonsterBase::CollisionOffset);
		++Iter;
	}
}

void NatureMissle_Water::PlayerDrag()
{
	if (false == CollisionCheckWithPlayer())
		return;

	PlayerStateType PlayerState = PlayerBase::MainPlayer->GetFSM()->GetCurStateByEnum();
	if (PlayerState == PlayerStateType::Jump)
		return;

	if (PlayerState == PlayerStateType::Damaged)
		return;

	PlayerBase::MainPlayer->SetPos(GetPos());
}


