#pragma once
#include <string>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class PlayerState;
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
	PlayerState* GetOwner();
	//Player FSM을 관리하는 객체 설정
	inline void SetOwner(PlayerState* _Owner)
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

	//(주로 자식의 Start에서 따로 호출됨)
	//플레이어가 사용되는 Level인 RoundLevel과 연결
	virtual void Start(PlayerCharacterType _CharacterType);

	//플레이어의 방향이 바뀌였다면 그 방향에 따라 애니메이션 전환
	virtual void Update(float _DeltaTime);

	//플레이어의 방향을 확인하고 해당 애니메이션을 동작
	virtual void EnterState();

	//애니메이션의 렌더러 끄기
	virtual void ExitState();

protected:
	//단지 EnterState와 ExitState를 override하지 않고 ChangeAnimation을 하기 위한 초기화값
	void SetAniRender(const std::string_view& _AniName);

	//자식들의 리소스를 로드하는데 도와주는 함수
	void ResourceLoad(const std::string_view& _ImageName, int _CutX, int _CutY);

	inline const std::string& GetAniName()
	{
		return AniName;
	}

	inline GameEngineRender* GetRender()
	{
		return Render;
	}

	RoundLevelBase* GetRoundLevel();

private:
	PlayerState*				Owner				= nullptr;
	PlayerBase*					Player				= nullptr;

	std::string					AniName			= "";
	GameEngineRender*	Render				= nullptr;

	const float4				PlayerScale		= float4{ 200.f, 200.f };
	RoundLevelBase*		RoundLevel		= nullptr;
};

