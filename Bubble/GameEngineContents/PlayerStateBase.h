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
	PlayerFSM* GetFSM();

	//Player FSM을 관리하는 객체 설정
	inline void SetFSM(PlayerFSM* _FSMPtr)
	{
		FSMPtr = _FSMPtr;
	}

	//Player 객체 반환
	PlayerBase* GetPlayer();

	//Player 객체 설정
	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}

	//애니메이션 생성 및 RoundLevel과 연결
	virtual void Start(PlayerCharacterType _CharacterType) = 0;

	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	virtual void Update(float _DeltaTime){}

	//플레이어의 방향을 확인하고 해당 애니메이션을 동작
	virtual void EnterState();

	//애니메이션의 렌더러 끄기
	virtual void ExitState(){}

protected:
	RoundLevelBase* GetRoundLevel();
	void ConnectRoundLevel();

	inline void SetAniName(const std::string_view& _AniName)
	{
		AniName = _AniName;
	}

	inline const std::string& GetAniName()
	{
		return AniName;
	}

	GameEngineRender* GetRender();

	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	void ChangeAniDir();

private:
	PlayerFSM*					FSMPtr				= nullptr;
	PlayerBase*					Player				= nullptr;
	RoundLevelBase*		RoundLevel		= nullptr;
	std::string					AniName			= "";
};



