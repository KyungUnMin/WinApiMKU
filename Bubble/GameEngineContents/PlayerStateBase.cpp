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


//자식들의 리소스를 로드하는데 도와주는 함수
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
		MsgAssert("해당 State를 초기화(Init함수 호출)시켜주지 않았습니다");
		return;
	}

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftAniPath))->Cut(CutInfo.first, CutInfo.second);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightAniPath))->Cut(CutInfo.first, CutInfo.second);
}

//Init을 사용하지 않고 특정 이미지를 직접 로드
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


//애니메이션 생성 및 RoundLevel과 연결
void PlayerStateBase::Start(PlayerCharacterType _CharacterType)
{
	CreateAnimation(_CharacterType);
	ConnectRoundLevel();
}


//애니메이션 만들기
void PlayerStateBase::CreateAnimation(PlayerCharacterType _CharacterType)
{
	//렌더링 생성 및 크기 설정
	Render = Player->CreateRender(RoundRenderOrder::Player1);
	Render->SetScale(PlayerScale);

	//캐릭터 타입
	int ImgXCnt = CutInfo.first;
	int AniIndex = static_cast<int>(_CharacterType) * ImgXCnt;

	std::string LeftAniName = MovableActor::LeftStr + AniName;
	std::string RightAniName = MovableActor::RightStr + AniName;

	//왼쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = LeftAniName,
		.ImageName = LeftAniPath,
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = AniInterval,
		.Loop = AniLoop
	});

	//오른쪽 애니메이션 생성
	GetRender()->CreateAnimation
	({
		.AnimationName = RightAniName,
		.ImageName = RightAniPath,
		.Start = AniIndex,
		.End = AniIndex + ImgXCnt - 1,
		.InterTimer = AniInterval,
		.Loop = AniLoop
	});

	//방향 받아오기
	const std::string StartDir = GetPlayer()->GetDirStr();

	//현재 방향에 따른 애니메이션 재생 설정
	GetRender()->ChangeAnimation(StartDir + AniName);

	//지금은 이 FSM상태가 아닐수 있기 때문에 렌더러 Off
	GetRender()->Off();
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



//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
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


RoundLevelBase* PlayerStateBase::GetRoundLevel()
{
	if (nullptr == RoundLevel)
	{
		MsgAssert("RoundLevel이 nullptr입니다.\nPlayerStateBase::Start를 호출해주지 않았습니다");
	}

	return RoundLevel;
}





//플레이어의 방향을 확인하고 해당 애니메이션을 동작
void PlayerStateBase::EnterState()
{
	const std::string StartDir = Player->GetDirStr();
	Render->ChangeAnimation(StartDir + AniName);
	Render->On();
}


//애니메이션의 렌더러 끄기
void PlayerStateBase::ExitState()
{
	Render->Off();
}