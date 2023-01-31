#pragma once
#include <string>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include "ContentsEnum.h"

class PlayerState;
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
	PlayerState* GetOwner();
	//Player FSM�� �����ϴ� ��ü ����
	inline void SetOwner(PlayerState* _Owner)
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

	//(�ַ� �ڽ��� Start���� ���� ȣ���)
	//�÷��̾ ���Ǵ� Level�� RoundLevel�� ����
	virtual void Start(PlayerCharacterType _CharacterType);

	//�÷��̾��� ������ �ٲ�ٸ� �� ���⿡ ���� �ִϸ��̼� ��ȯ
	virtual void Update(float _DeltaTime);

	//�÷��̾��� ������ Ȯ���ϰ� �ش� �ִϸ��̼��� ����
	virtual void EnterState();

	//�ִϸ��̼��� ������ ����
	virtual void ExitState();

protected:
	//���� EnterState�� ExitState�� override���� �ʰ� ChangeAnimation�� �ϱ� ���� �ʱ�ȭ��
	void SetAniRender(const std::string_view& _AniName);

	//�ڽĵ��� ���ҽ��� �ε��ϴµ� �����ִ� �Լ�
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

