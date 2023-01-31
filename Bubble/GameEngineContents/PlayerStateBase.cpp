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

//�ڽĵ��� ���ҽ��� �ε��ϴµ� �����ִ� �Լ�
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



//(�ַ� �ڽ��� Start���� ���� ȣ���)
//�÷��̾ ���Ǵ� Level�� RoundLevel�� ����
void PlayerStateBase::Start(PlayerCharacterType _CharacterType)
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
		MsgAssert("RoundLevel�� nullptr�Դϴ�.\nPlayerStateBase::Start�� ȣ�������� �ʾҽ��ϴ�");
	}

	return RoundLevel;
}


//���� EnterState�� ExitState�� override���� �ʰ� ChangeAnimation�� �ϱ� ���� �Լ�
void PlayerStateBase::SetAniRender(const std::string_view& _AniName)
{
	Render = Player->CreateRender(RoundRenderOrder::Player1);
	Render->SetScale(PlayerScale);
	AniName = _AniName;
}


//�÷��̾��� ������ Ȯ���ϰ� �ش� �ִϸ��̼��� ����
void PlayerStateBase::EnterState()
{
	const std::string StartDir = Player->GetDirStr();
	Render->ChangeAnimation(StartDir + GetAniName());
	Render->On();
}

//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
void PlayerStateBase::Update(float _DeltaTime)
{
	if (false == GetPlayer()->IsDirChanged())
		return;

	const std::string NowDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(NowDir + GetAniName());
}

//�ִϸ��̼��� ������ ����
void PlayerStateBase::ExitState()
{
	Render->Off();
}