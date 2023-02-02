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


//�ڽĵ��� ���ҽ��� �ε��ϴµ� �����ִ� �Լ�
void PlayerStateBase::ResourceLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");

	if (LeftAniPath.empty() || RightAniPath.empty())
	{
		MsgAssert("�ش� State�� �ʱ�ȭ(Init�Լ� ȣ��)�������� �ʾҽ��ϴ�");
		return;
	}

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftAniPath))->Cut(CutInfo.first, CutInfo.second);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightAniPath))->Cut(CutInfo.first, CutInfo.second);
}

//Init�� ������� �ʰ� Ư�� �̹����� ���� �ε�
void PlayerStateBase::ResourceLoad(const std::string_view& _ImagePath, const std::pair<int, int>& _CutInfo)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Player");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(_ImagePath))->Cut(_CutInfo.first, _CutInfo.second);
}


//�ִϸ��̼� ���� �� RoundLevel�� ����
void PlayerStateBase::Start(PlayerCharacterType _CharacterType)
{
	CreateAnimation(_CharacterType);
	ConnectRoundLevel();
}


//�ִϸ��̼� �����
void PlayerStateBase::CreateAnimation(PlayerCharacterType _CharacterType)
{
	//������ ���� �� ũ�� ����
	Render = Player->CreateRender(RoundRenderOrder::Player1);
	Render->SetScale(PlayerScale);

	//ĳ���� Ÿ��
	int ImgXCnt = CutInfo.first;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	std::string LeftAniName = MovableActor::LeftStr + AniName;
	std::string RightAniName = MovableActor::RightStr + AniName;

	//���� �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = LeftAniPath,
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = AniInterval,
		.Loop = AniLoop
	});

	//������ �ִϸ��̼� ����
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = RightAniPath,
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = AniInterval,
		.Loop = AniLoop
	});

	//���� �޾ƿ���
	const std::string StartDir = GetPlayer()->GetDirStr();

	//���� ���⿡ ���� �ִϸ��̼� ��� ����
	GetRender()->ChangeAnimation(StartDir + AniName);

	//������ �� FSM���°� �ƴҼ� �ֱ� ������ ������ Off
	GetRender()->Off();
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



//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
void PlayerStateBase::Update(float _DeltaTime)
{
	if (false == GetPlayer()->IsDirChanged())
		return;

	const std::string NowDir = GetPlayer()->GetDirStr();
	GetRender()->ChangeAnimation(NowDir + AniName);
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


RoundLevelBase* PlayerStateBase::GetRoundLevel()
{
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel�� nullptr�Դϴ�.\nPlayerStateBase::Start�� ȣ�������� �ʾҽ��ϴ�");
	}

	return RoundLevel;
}





//�÷��̾��� ������ Ȯ���ϰ� �ش� �ִϸ��̼��� ����
void PlayerStateBase::EnterState()
{
	const std::string StartDir = Player->GetDirStr();
	Render->ChangeAnimation(StartDir + AniName);
	Render->On();
}


//�ִϸ��̼��� ������ ����
void PlayerStateBase::ExitState()
{
	Render->Off();
}