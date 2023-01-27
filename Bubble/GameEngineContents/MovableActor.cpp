#include "MovableActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsDefine.h"
#include "PlayerState.h"
#include "Gravity.h"

const std::string MovableActor::LeftStr	= "Left_";
const std::string MovableActor::RightStr	= "Right_";

MovableActor::MovableActor()
{

}

MovableActor::~MovableActor()
{

}


void MovableActor::Update(float _DeltaTime)
{
	CheckDirection();
}

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

	MsgAssert("������ ���ʰ� ���������θ� �����մϴ�\n ���� ������ �߸��Ǿ����ϴ�");
	return float4::Zero;
}