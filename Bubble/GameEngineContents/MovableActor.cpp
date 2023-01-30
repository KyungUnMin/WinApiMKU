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
	//이번 프레임에 방향이 바뀌였는지 체크
	CheckDirection();
}

//이번 프레임에 방향이 바뀌였는지 체크
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


//이 물체가 현재 바라보고 있는 방향을 float4(벡터)로 반환
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

	//혹시 몰라서 처리한 예외상황
	MsgAssert("방향은 왼쪽과 오른쪽으로만 존재합니다\n 현재 방향은 잘못되었습니다");
	return float4::Zero;
}