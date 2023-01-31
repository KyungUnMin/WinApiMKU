#include "PlayerStateBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"
#include "RoundLevelBase.h"

PlayerStateBase::PlayerStateBase()
{
}

PlayerStateBase::~PlayerStateBase()
{
}




PlayerState* PlayerStateBase::GetOwner()
{
	if (nullptr == Owner)
	{
		MsgAssert("이 State에 Owner를 지정해주지 않았습니다");
		return nullptr;
	}

	return Owner;
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

//자식들의 리소스를 로드하는데 도와주는 함수
void PlayerStateBase::ResourceLoad(const std::string_view& _ImageName, int _CutX, int _CutY)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(_ImageName))->Cut(_CutX, _CutY);
}



//(주로 자식의 Start에서 따로 호출됨)
//플레이어가 사용되는 Level인 RoundLevel과 연결
void PlayerStateBase::Start(PlayerCharacterType _CharacterType)
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
		MsgAssert("RoundLevel이 nullptr입니다.\nPlayerStateBase::Start를 호출해주지 않았습니다");
	}

	return RoundLevel;
}


//단지 EnterState와 ExitState를 override하지 않고 ChangeAnimation을 하기 위한 함수
void PlayerStateBase::SetAniRender(const std::string_view& _AniName)
{
	Render = Player->CreateRender(RoundRenderOrder::Player1);
	Render->SetScale(PlayerScale);
	AniName = _AniName;
}


//플레이어의 방향을 확인하고 해당 애니메이션을 동작
void PlayerStateBase::EnterState()
{
	const std::string StartDir = Player->GetDirStr();
	Render->ChangeAnimation(StartDir + GetAniName());
	Render->On();
}

//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
void PlayerStateBase::Update(float _DeltaTime)
{
	if (false == GetPlayer()->IsDirChanged())
		return;

	const std::string NowDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(NowDir + GetAniName());
}

//애니메이션의 렌더러 끄기
void PlayerStateBase::ExitState()
{
	Render->Off();
}