#include "PlayerStateBase.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

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
		MsgAssert("�� State�� Owner�� ���������� �ʾҽ��ϴ�");
		return nullptr;
	}

	return Owner;
}

PlayerBase* PlayerStateBase::GetPlayer()
{
	if (nullptr == Player)
	{
		MsgAssert("�� State�� Player�� ���������� �ʾҽ��ϴ�");
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
