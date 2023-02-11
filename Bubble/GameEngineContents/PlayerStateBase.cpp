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



//�÷��̾ ���Ǵ� Level�� RoundLevel�� ����
void PlayerStateBase::ConnectRoundLevel()
{
	RoundLevel = dynamic_cast<RoundLevelBase*>(GetPlayer()->GetLevel());
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel�� ���� ������ ����Ǿ� ���� �ʽ��ϴ�");
	}
}



RoundLevelBase* PlayerStateBase::GetRoundLevel()
{
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel�� ����Ǿ� ���� �ʽ��ϴ�.\n(ConnectRoundLevel()�� ȣ�������� �ʾҽ��ϴ�)");
		return nullptr;
	}

	return RoundLevel;
}






GameEngineRender* PlayerStateBase::GetRender()
{
	if (nullptr == FSMPtr)
	{
		MsgAssert("���� State�� PlayerFSM�� ���������� �ʾҽ��ϴ�");
		return nullptr;
	}

	GameEngineRender* RenderPtr = FSMPtr->GetRender();
	if (nullptr == RenderPtr)
	{
		MsgAssert("�÷��̾ Render�� �������� �ʾҽ��ϴ�");
		return nullptr;
	}

	return RenderPtr;
}






PlayerFSM* PlayerStateBase::GetFSM()
{
	if (nullptr == FSMPtr)
	{
		MsgAssert("�� State�� Owner�� ���������� �ʾҽ��ϴ�");
		return nullptr;
	}

	return FSMPtr;
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





//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
void PlayerStateBase::ChangeAniDir()
{
	if (false == GetPlayer()->IsDirChanged())
		return;

	const std::string NowDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(NowDir + AniName);
}



//�÷��̾� ���� + �ִϸ��̼��̸�
const std::string PlayerStateBase::GetAniNamePlusDir(const std::string_view& _AniName)
{
	const std::string NowDir = GetPlayer()->GetDirStr();
	return NowDir + _AniName.data();
}

//�÷��̾��� ������ Ȯ���ϰ� �ش� �ִϸ��̼��� ����
void PlayerStateBase::EnterState()
{
	GetRender()->ChangeAnimation(GetAniNamePlusDir(AniName));
}
