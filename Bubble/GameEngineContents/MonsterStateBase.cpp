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
		MsgAssert("���� State�� ���͸� ���������� �ʾҽ��ϴ�");
		return;
	}

	if (nullptr == GetFSM())
	{
		MsgAssert("���� State�� FSM�� ���������� �ʾҽ��ϴ�");
		return;
	}
}

void MonsterStateBase::EnterState()
{
	if (true == NowAniName.empty())
	{
		MsgAssert("���� ������ �ִϸ��̼��� ���������� �ʾҽ��ϴ�");
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
		MsgAssert("�� ���Ϳ��� GameEngineRender�� ��������� �ʾҽ��ϴ�");
		return;
	}

	RenderPtr->CreateAnimation(_Param);
}

