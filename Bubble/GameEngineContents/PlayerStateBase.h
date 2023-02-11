#pragma once
#include <string>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class PlayerFSM;
class PlayerBase;
class GameEngineRender;
class RoundLevelBase;

//��� �÷��̾� FSM�� ���̽��� �Ǵ� Ŭ����
class PlayerStateBase
{
public:
	PlayerStateBase();
	virtual ~PlayerStateBase() = 0;

	PlayerStateBase(const PlayerStateBase& _Other) = delete;
	PlayerStateBase(PlayerStateBase&& _Other) noexcept = delete;
	PlayerStateBase& operator=(const PlayerStateBase& _Other) = delete;
	PlayerStateBase& operator=(const PlayerStateBase&& _Other) noexcept = delete;



	//Player FSM�� �����ϴ� ��ü ��ȯ
	PlayerFSM* GetFSM();

	//Player FSM�� �����ϴ� ��ü ����
	inline void SetFSM(PlayerFSM* _FSMPtr)
	{
		FSMPtr = _FSMPtr;
	}

	//Player ��ü ��ȯ
	PlayerBase* GetPlayer();

	//Player ��ü ����
	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}

	//�ִϸ��̼� ���� �� RoundLevel�� ����
	virtual void Start(PlayerCharacterType _CharacterType) = 0;

	//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
	virtual void Update(float _DeltaTime){}

	//�÷��̾��� ������ Ȯ���ϰ� �ش� �ִϸ��̼��� ����
	virtual void EnterState();

	//�ִϸ��̼��� ������ ����
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

	//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
	void ChangeAniDir();

private:
	PlayerFSM*					FSMPtr				= nullptr;
	PlayerBase*					Player				= nullptr;
	RoundLevelBase*		RoundLevel		= nullptr;
	std::string					AniName			= "";
};



