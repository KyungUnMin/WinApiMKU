#include "MonsterStateBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MonsterBase.h"

MonsterStateBase::MonsterStateBase()
{
	
}

MonsterStateBase::~MonsterStateBase()
{

}

void MonsterStateBase::Start()
{
	if (nullptr == GetMonster())
	{
		MsgAssert("현재 State에 몬스터를 연결해주지 않았습니다");
		return;
	}

	if (nullptr == GetFSM())
	{
		MsgAssert("현재 State에 FSM을 연결해주지 않았습니다");
		return;
	}
}

void MonsterStateBase::EnterState()
{
	if (true == NowAniName.empty())
	{
		MsgAssert("현재 상태의 애니메이션을 설정해주지 않았습니다");
		return;
	}

	const std::string NowDir = Monster->GetDirStr();
	GameEngineRender* RenderPtr = Monster->GetRender();
	RenderPtr->ChangeAnimation(NowDir + NowAniName);
}



void MonsterStateBase::CreateAnimation(const FrameAnimationParameter& _Param)
{
	GameEngineRender* RenderPtr = GetMonster()->GetRender();

	if (nullptr == RenderPtr)
	{
		MsgAssert("이 몬스터에는 GameEngineRender를 만들어주지 않았습니다");
		return;
	}

	RenderPtr->CreateAnimation(_Param);
}

