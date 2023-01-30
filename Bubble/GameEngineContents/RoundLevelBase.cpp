#include "RoundLevelBase.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "BackGround.h"
#include "Player_Bubblun.h"
#include "Player_Bobblun.h"
#include "Player_Kululun.h"
#include "Player_Cororon.h"

RoundLevelBase::RoundLevelBase()
{

}

RoundLevelBase::~RoundLevelBase()
{

}



//������ ������ �浹ü�� �ε��ϴ� �Լ�
void RoundLevelBase::LoadObstacle(const std::string_view& _RoundName, int _X, int _Y)
{
	//��� RoundLevel�� Obstacle�� �� ������ ����Ǿ� �ִ�
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("RoundRooms");
	Dir.Move("Obstacle");

	//���� �浹ü Load
	//"Round" + _RoundName + "_Collider.bmp"
	ImageName += _RoundName.data();
	ColliderImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName + "_Collider.bmp"));
	ColliderImage->Cut(_X, _Y);

	//���� ���� �̹��� �ε�
	//"Round" + _RoundName + "_Obstacle.bmp"
	ImageName += "_Obstacle.bmp";
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(ImageName))->Cut(_X, _Y);

	Obstacles = CreateActor<BackGround>();
	Obstacles->RenderReserve(_X * _Y);
}


//������ ������ �����ϴ� �Լ�
void RoundLevelBase::CreateObstacle(const float4& _ArrangeDir, int _Order)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//���� ������ ���α�
	for (size_t i = 0; i < Obstacles->GetRenderCapacity(); ++i)
	{
		GameEngineRender* Render = Obstacles->CreateRender(ImageName, _Order);
		Render->SetFrame(static_cast<int>(i));
		Render->Off();
	}

	//���ڷ� ���� _ArrangeDir�������� 0�� Render�� ȭ�� �߾ӿ� ������ ����(0�� Render�� On)
	ArrangeStage(_ArrangeDir, 0);

	//Stage�� ��ȯ�ɶ� Stage�̵����� ����
	MoveDir = -(_ArrangeDir);
}


//���ڷ� ���� _Dir�������� _CenterIndex�� Render�� ȭ�� �߾ӿ� ������ ����(_CenterIndex�� Render�� On)
void RoundLevelBase::ArrangeStage(float4 _Dir, size_t _CenterIndex)
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	for (size_t i = 0; i < Obstacles->GetRenderSize(); ++i)
	{
		GameEngineRender* Render = Obstacles->GetRender(i);
		float4 Offset = float4::Zero;

		//���� ������ �������϶�
		if (_Dir == float4::Right)
		{
			//_CenterIndex�� ȭ���߾ӿ� ������ ����
			Offset = _Dir * ScreenSize.x * static_cast<float>(i - _CenterIndex);
		}

		//���� ������ �Ʒ��϶�
		else if (_Dir == float4::Down)
		{
			//_CenterIndex�� ȭ���߾ӿ� ������ ����
			Offset = _Dir * ScreenSize.y * static_cast<float>(i - _CenterIndex);
		}
		else
		{
			MsgAssert("float4::Right �Ǵ� float4::Down �������θ� ������ ������ �� �ֽ��ϴ�.");
		}

		Render->SetPosition(Offset);
		Render->Off();
	}

	NowIndex = _CenterIndex;

	//_CenterIndex�� Render�� On
	Obstacles->GetRender(NowIndex)->On();
}


//���� Stage�� �̵��ϴ� �Լ�
bool RoundLevelBase::MoveToNextStage()
{
	//�̹� Stage�� �̵����̶�� Return
	if (true == IsMoving)
		return false;

	//�̹� ���������� �������̿��ٸ� false�� ����
	if (NowIndex + 1 == Obstacles->GetRenderSize())
	{
		return false;
	}

	//IsMoving�� true�϶� Update���� Stage�� �̵���
	IsMoving = true;

	//���� Stage�� ������ On
	Obstacles->GetRender(NowIndex + 1)->On();
	return true;
}



void RoundLevelBase::Update(float _DeltaTime)
{
	//IsMoving�� true�϶��� Stage�� �̵���
	if (false == IsMoving)
		return;

	//��� ������������ �̵�
	for (size_t i = 0; i < Obstacles->GetRenderSize(); ++i)
	{
		GameEngineRender* Render = Obstacles->GetRender(i);
		float4 Offset = Render->GetPosition();
		Offset += MoveDir * MoveSpeed * _DeltaTime;
		Render->SetPosition(Offset);
	}

	//���� ���������� Render
	GameEngineRender* NextStage = Obstacles->GetRender(NowIndex + 1);

	//���� ���������� Offset�� ȭ�� �߽ɺ��ٵ� �� �������ٸ� return �Ʒ� �ڵ� ����
	float4 NextOffset = NextStage->GetPosition();
	if (0 <= NextOffset.x && 0 <= NextOffset.y)
		return;

	//���� Stage�� �߽����� Stage�� �����ϰ� NowIndex�� 1������Ű�� ������ Render�� Off
	ArrangeStage(-MoveDir, NowIndex + 1);
	IsMoving = false;
}



//NowIndex�� ���� Round���� ������ Stage���� �˷��ִ� �Լ�
bool RoundLevelBase::IsLastStage()
{
	return (NowIndex + 1) == Obstacles->GetRenderSize();
}


//���ڷ� �޴� _Pos�� ������ ������ ���� ���� ������ �˷��ִ� �Լ�
bool RoundLevelBase::IsBlockPos(const float4& _Pos)
{
	//���� Stage�� �°� Offset�� ����	(3�� ����������� �ػ�.x * 3)
	float4 Offset = ColliderImage->GetCutData(static_cast<int>(NowIndex)).GetStartPos();

	//�ش� ������ ���� ����
	DWORD Color = ColliderImage->GetPixelColor(Offset + _Pos, RGB(0, 0, 0));

	//�������̶�� ���� �浹ü�� �����ִ°�
	return Color == RGB(0,0,0);
}


//PlayerCharacterType Ÿ�Կ� ���� �÷��̾ �����ϴ� �Լ�
void RoundLevelBase::CreatePlayer(PlayerCharacterType _Type)
{
	SelectedCharacter = _Type;

	//�̹� �� �÷��̾ �����Ѵٸ�(ReStart �� ��� �̹� ������ ���� ����)
	if (nullptr != Player)
	{
		Player->Death();
		Player = nullptr;
	}

	switch (_Type)
	{
	case PlayerCharacterType::BUBBLUN:
		Player = CreateActor<Player_Bubblun>();
		break;
	case PlayerCharacterType::BOBBLUN:
		Player = CreateActor <Player_Bobblun>();
		break;
	case PlayerCharacterType::KULULUN:
		Player = CreateActor <Player_Kululun>();
		break;
	case PlayerCharacterType::CORORON:
		Player = CreateActor <Player_Cororon>();
		break;
	}

}


//������ ��ȯ�ɶ� ���� �����ϰ� ����
void RoundLevelBase::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	IsMoving = false; 

	RoundLevelBase* NextRoundLevel = dynamic_cast<RoundLevelBase*>(_NextLevel);

	//���������� Round������ �ƴѰ��
	if (nullptr == NextRoundLevel)
		return;

	//���� ������ �÷��̾� ������Ű��
	NextRoundLevel->CreatePlayer(SelectedCharacter);
}
