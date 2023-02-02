#include "MovableActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"

const float				MovableActor::ColliderRange	= 20.f;
const std::string		MovableActor::LeftStr				= "Left_";
const std::string		MovableActor::RightStr				= "Right_";

MovableActor::MovableActor()
{

}

MovableActor::~MovableActor()
{

}


//�� �κ��� ���� ����� ������
//�÷��̾�� ���ӵǾ� ����
//�̹� �����ӿ� ������ �ٲ���� üũ
void MovableActor::CheckDirection()
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