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


//이 부분이 지금 상당히 문제다
//플레이어에만 종속되어 있음
//이번 프레임에 방향이 바뀌였는지 체크
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
		MsgAssert("방향설정은 float4::Right 와 float4::Left로만 설정할 수 있습니다");
	}
}