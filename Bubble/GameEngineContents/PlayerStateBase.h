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
	PlayerFSM* GetOwner();

	//Player FSM�� �����ϴ� ��ü ����
	inline void SetOwner(PlayerFSM* _Owner)
	{
		Owner = _Owner;
	}

	//Player ��ü ��ȯ
	PlayerBase* GetPlayer();

	//Player ��ü ����
	inline void SetPlayer(PlayerBase* _Player)
	{
		Player = _Player;
	}



	//�ִϸ��̼� ���� �� RoundLevel�� ����
	virtual void Start(PlayerCharacterType _CharacterType);

	//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
	virtual void Update(float _DeltaTime);

	//�÷��̾��� ������ Ȯ���ϰ� �ش� �ִϸ��̼��� ����
	virtual void EnterState();

	//�ִϸ��̼��� ������ ����
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



	//�ڽĵ��� ���ҽ��� �ε��ϴµ� �����ִ� �Լ�
	void ResourceLoad();

	//Init�� ������� �ʰ� Ư�� �̹����� ���� �ε�
	void ResourceLoad(const std::string_view& _ImagePath, const std::pair<int,int>& _CutInfo);


	inline GameEngineRender* GetRender()
	{
		return Render;
	}

	RoundLevelBase* GetRoundLevel();

private:
	//Init�� ���Ǵ� ����
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


	//�ִϸ��̼� �����
	void CreateAnimation(PlayerCharacterType _CharacterType);

	//�÷��̾ ���Ǵ� Level�� RoundLevel�� ����
	void ConnectRoundLevel();
};



