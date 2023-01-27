#include "PlayerStateBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "PlayerBase.h"

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



void PlayerStateBase::InitState(const std::string_view& _AniName)
{
	Render = Player->CreateRender(RoundRenderOrder::Player1);
	Render->SetScale(PlayerScale);
	AniName = _AniName;
}

void PlayerStateBase::EnterState()
{
	const std::string StartDir = Player->GetDirStr();
	Render->ChangeAnimation(StartDir + GetAniName());
	Render->On();
}

void PlayerStateBase::ExitState()
{
	Render->Off();
}