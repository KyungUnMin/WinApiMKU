#include "PlayerStateBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "RoundLevelBase.h"
#include "PlayerFSM.h"


PlayerStateBase::PlayerStateBase()
{
}

PlayerStateBase::~PlayerStateBase()
{
}



//플레이어가 사용되는 Level인 RoundLevel과 연결
void PlayerStateBase::ConnectRoundLevel()
{
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetPlayer()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel이 현재 레벨과 연결되어 있지 않습니다");
	}
}



RoundLevelBase* PlayerStateBase::GetRoundLevel()
{
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel이 연결되어 있지 않습니다.\n(ConnectRoundLevel()을 호출해주지 않았습니다)");
		return nullptr;
	}

	return RoundLevel;
}






GameEngineRender* PlayerStateBase::GetRender()
{
	if (nullptr == FSMPtr)
	{
		MsgAssert("현재 State와 PlayerFSM을 연결해주지 않았습니다");
		return nullptr;
	}

	GameEngineRender* RenderPtr = FSMPtr->GetRender();
	if (nullptr == RenderPtr)
	{
		MsgAssert("플레이어가 Render를 생성하지 않았습니다");
		return nullptr;
	}

	return RenderPtr;
}






PlayerFSM* PlayerStateBase::GetFSM()
{
	if (nullptr == FSMPtr)
	{
		MsgAssert("이 State에 Owner를 지정해주지 않았습니다");
		return nullptr;
	}

	return FSMPtr;
}

PlayerBase* PlayerStateBase::GetPlayer()
{
	if (nullptr == Player)
	{
		MsgAssert("이 State에 Player를 지정해주지 않았습니다");
		return nullptr;
	}

	return Player;
}





//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
void PlayerStateBase::ChangeAniDir()
{
	if (false == GetPlayer()->IsDirChanged())
		return;

	const std::string NowDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(NowDir + AniName);
}



//플레이어 방향 + 애니메이션이름
const std::string PlayerStateBase::GetAniNamePlusDir(const std::string_view& _AniName)
{
	const std::string NowDir = GetPlayer()->GetDirStr();
	return NowDir + _AniName.data();
}

//플레이어의 방향을 확인하고 해당 애니메이션을 동작
void PlayerStateBase::EnterState()
{
	GetRender()->ChangeAnimation(GetAniNamePlusDir(AniName));
}
