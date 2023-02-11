#include "MovableActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsDefine.h"
#include "PlayerFSM.h"
#include "RoundLevelBase.h"

const std::string		MovableActor::LeftStr				= "Left_";
const std::string		MovableActor::RightStr				= "Right_";

MovableActor::MovableActor()
{

}

MovableActor::~MovableActor()
{

}


void MovableActor::Start()
{
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("MovableActor�� RoundLevelBase�� ��ӹ��� ���������� ������ �� �ֽ��ϴ�");
		return;
	}

}

//�̹� �����ӿ� ������ �ٲ���� üũ
void MovableActor::Update(float _DeltaTime)
{
	DirChanged = false;

	if (true == GameEngineInput::IsPress(PLAYER_LEFT))
	{
		DirChanged = (Dir != MovableActor::LeftStr);
		Dir = MovableActor::LeftStr;
	}
	else if (true == GameEngineInput::IsPress(PLAYER_RIGHT))
	{
		DirChanged = (Dir != MovableActor::RightStr);
		Dir = MovableActor::RightStr;
	}

}



RoundLevelBase* MovableActor::GetRoundLevel()
{
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel�� �����Ű�� �ʾҽ��ϴ�\n(MovableActor::Startȣ��)");
		return nullptr;
	}

	return RoundLevel;
}







//�� ��ü�� ���� �ٶ󺸰� �ִ� ������ float4(����)�� ��ȯ
const float4& MovableActor::GetDirVec()
{
	if (MovableActor::RightStr == Dir)
	{
		return float4::Right;
	}
	else if (MovableActor::LeftStr == Dir)
	{
		return float4::Left;
	}

	//Ȥ�� ���� ó���� ���ܻ�Ȳ
	MsgAssert("������ ���ʰ� ���������θ� �����մϴ�\n ���� ������ �߸��Ǿ����ϴ�");
	return float4::Zero;
}



void MovableActor::SetDir(const float4& _Dir)
{
	if (float4::Right == _Dir)
	{
		Dir = RightStr;
	}
	else if (float4::Left == _Dir)
	{
		Dir = LeftStr;
	}
	else
	{
		MsgAssert("���⼳���� float4::Right �� float4::Left�θ� ������ �� �ֽ��ϴ�");
	}
}




//�� �ٷ� �Ʒ��� ������ Ȯ��
bool MovableActor::IsGround(const float4& _CollisionScale)
{
	//�浹ü ���� ����(�� ������ �ٷ� �Ʒ��� üũ)
	float4 CenterCheckPos = GetPos() + float4::Down;
	float4 LeftCheckPos = CenterCheckPos + (float4::Left * _CollisionScale.half());
	float4 RightCheckPos = CenterCheckPos + (float4::Right * _CollisionScale.half());

	//�ϳ��� ���������� ��
	if (true == RoundLevel->IsBlockPos(CenterCheckPos))
		return true;

	if (true == RoundLevel->IsBlockPos(LeftCheckPos))
		return true;

	if (true == RoundLevel->IsBlockPos(RightCheckPos))
		return true;


	return false;
}

bool MovableActor::MoveHorizon(float _Speed, const float4& _CollisionScale, float _DeltaTime)
{
	float4 Dir = GetDirVec();
	float4 NextPos = GetPos() + (Dir * _Speed * _DeltaTime);
	float4 CheckPos = NextPos + Dir * _CollisionScale.half();

	//�̵���Ű���� ��ġ�� ���̶�� �̵� ����
	if (true == RoundLevel->IsBlockPos(CheckPos))
		return false;

	//�̵�
	SetPos(NextPos);
	return true;
}

void MovableActor::RaiseOnGround(const float4& _CollisionScale)
{
	while (IsGround(_CollisionScale))
	{
		SetMove(float4::Up);
	}

	SetMove(float4::Down);
}


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "PlayerBase.h"

void MovableActor::Render(float _DeltaTime)
{
	//�ӽ� �׽�Ʈ �ڵ�
	float4 Pos[3];
	Pos[0] = GetPos() + float4::Down;
	Pos[1] = Pos[0] + (float4::Left * PlayerBase::CollisionScale.half());
	Pos[2] = Pos[0] + (float4::Right * PlayerBase::CollisionScale.half());

	HDC Hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

	for (size_t i = 0; i < 3; ++i)
	{
		Rectangle(Hdc, Pos[i].ix() - 1, Pos[i].iy() - 1, Pos[i].ix() + 1, Pos[i].iy() + 1);
	}


}



