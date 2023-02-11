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
		MsgAssert("MovableActor는 RoundLevelBase를 상속받은 레벨에서만 생성할 수 있습니다");
		return;
	}

}

//이번 프레임에 방향이 바뀌였는지 체크
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
		MsgAssert("RoundLevel을 연결시키지 않았습니다\n(MovableActor::Start호출)");
		return nullptr;
	}

	return RoundLevel;
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




//내 바로 아래가 땅인지 확인
bool MovableActor::IsGround(const float4& _CollisionScale)
{
	//충돌체 가로 범위(이 엑터의 바로 아래를 체크)
	float4 CenterCheckPos = GetPos() + float4::Down;
	float4 LeftCheckPos = CenterCheckPos + (float4::Left * _CollisionScale.half());
	float4 RightCheckPos = CenterCheckPos + (float4::Right * _CollisionScale.half());

	//하나라도 걸쳐있으면 땅
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

	//이동시키려는 위치가 벽이라면 이동 안함
	if (true == RoundLevel->IsBlockPos(CheckPos))
		return false;

	//이동
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
	//임시 테스트 코드
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



