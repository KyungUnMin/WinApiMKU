#pragma once
#include <string>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class PlayerFSM;
class PlayerBase;
class GameEngineRender;
class RoundLevelBase;

//모든 플레이어 FSM의 베이스가 되는 클래스
class PlayerStateBase
{
public:
	PlayerStateBase();
	virtual ~PlayerStateBase() = 0;

	PlayerStateBase(const PlayerStateBase& _Other) = delete;
	PlayerStateBase(PlayerStateBase&& _Other) noexcept = delete;
	PlayerStateBase& operator=(const PlayerStateBase& _Other) = delete;
	PlayerStateBase& operator=(const PlayerStateBase&& _Other) noexcept = delete;



	//Player FSM을 관리하는 객체 반환
	PlayerFSM* GetOwner();

	//Player FSM을 관리하는 객체 설정
	inline void SetOwner(PlayerFSM* _Owner)
	{
		Owner = _Owner;
	}

	//Player 객체 반환
	PlayerBase* GetPlayer();

	//Player 객체 설정
	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}



	//애니메이션 생성 및 RoundLevel과 연결
	virtual void Start(PlayerCharacterType _CharacterType);

	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	virtual void Update(float _DeltaTime);

	//플레이어의 방향을 확인하고 해당 애니메이션을 동작
	virtual void EnterState();

	//애니메이션의 렌더러 끄기
	virtual void ExitState();

protected:
	void Init(
		const std::string_view& _LeftAniPath,
		const std::string_view& _RightAniPath,
		const std::string_view& _AniName,
		const std::pair<int, int>& _CutInfo,
		float _AniInterval = 0.1f,
		bool _AniLoop = true)
	{
		LeftAniPath = _LeftAniPath;
		RightAniPath = _RightAniPath;
		AniName = _AniName;
		CutInfo = _CutInfo;
		AniInterval = _AniInterval;
		AniLoop = _AniLoop;
	}



	//자식들의 리소스를 로드하는데 도와주는 함수
	void ResourceLoad();

	//Init을 사용하지 않고 특정 이미지를 직접 로드
	void ResourceLoad(const std::string_view& _ImagePath, const std::pair<int,int>& _CutInfo);


	inline GameEngineRender* GetRender()
	{
		return Render;
	}

	RoundLevelBase* GetRoundLevel();

private:
	//Init에 사용되는 정보
	std::string					LeftAniPath		= "";
	std::string					RightAniPath	= "";
	std::string					AniName			= "";
	std::pair<int, int> 		CutInfo;
	float							AniInterval		= 0.1f;
	bool								AniLoop			= true;

	RoundLevelBase*		RoundLevel		= nullptr;
	const float4				PlayerScale		= float4{ 200.f, 200.f };



	PlayerFSM*				Owner				= nullptr;
	PlayerBase*					Player				= nullptr;
	GameEngineRender*	Render				= nullptr;


	//애니메이션 만들기
	void CreateAnimation(PlayerCharacterType _CharacterType);

	//플레이어가 사용되는 Level인 RoundLevel과 연결
	void ConnectRoundLevel();
};



