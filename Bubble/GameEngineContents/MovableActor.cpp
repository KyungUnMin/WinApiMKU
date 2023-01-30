#include "MovableActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"

const float				MovableActor::ColliderRange	= 30.f;
const std::string		MovableActor::LeftStr				= "Left_";
const std::string		MovableActor::RightStr				= "Right_";

MovableActor::MovableActor()
{

}

MovableActor::~MovableActor()
{

}


void MovableActor::Update(float _DeltaTime)
{
	//�̹� �����ӿ� ������ �ٲ���� üũ
	CheckDirection();
}

//�̹� �����ӿ� ������ �ٲ���� üũ
void MovableActor::CheckDirection()
{
	DirChanged = false;

	if (true == GameEngineInput::IsPress("PlayerLeft"))
	{
		DirChanged = (Dir != MovableActor::LeftStr);
		Dir = MovableActor::LeftStr;
	}
	else if (true == GameEngineInput::IsPress("PlayerRight"))
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