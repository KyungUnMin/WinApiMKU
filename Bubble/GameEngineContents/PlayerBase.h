#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class GameEngineCollision;
class GameEngineRender;
class PlayerFSM;
class BubbleSpawner;

//��� �÷��̾� Ŭ������ �θ� �Ǵ� �߻� Ŭ����
class PlayerBase : public MovableActor
{
public:
	static PlayerBase* MainPlayer;

	static const float4 CollisionOffset;
	static const float4 CollisionScale;

	PlayerBase();
	virtual ~PlayerBase() = 0;

	PlayerBase(const PlayerBase& _Other) = delete;
	PlayerBase(PlayerBase&& _Other) noexcept = delete;
	PlayerBase& operator=(const PlayerBase& _Other) = delete;
	PlayerBase& operator=(const PlayerBase&& _Other) noexcept = delete;

	PlayerCharacterType GetCharacterType();

	inline  PlayerFSM* GetFSM()
	{
		return FSMPtr;
	}

	inline GameEngineCollision* GetCollision()
	{
		return CollisionPtr;
	}
	
	inline int GetLifeCount()
	{
		return lifeCnt;
	}

	inline GameEngineRender* GetRender()
	{
		return RenderPtr;
	}

	//�����ʿ��� ȣ���
	void AttackPlayer();

	//FSM�� Damaged State�� ���������� �����
	inline void ResetAliveTime()
	{
		AliveLiveTime = 0.f;
	}

protected:
	//�÷��̾ ����� ������Ʈ�� ����� �ʱ�ȭ
	void Start() override;

	//������ üũ�ϰ� ������Ʈ���� ����
	void Update(float _DeltaTime) final;
	void Render(float _DeltaTime) override;

	inline void SetCharacterType(PlayerCharacterType _Type)
	{
		CharcterType = _Type;
	}


private:
	const float4					PlayerRenderScale = float4{ 200.f, 200.f };
	GameEngineRender*		RenderPtr				= nullptr;

	PlayerFSM*						FSMPtr						= nullptr;
	BubbleSpawner*				BBSpawner				= nullptr;

	PlayerCharacterType		CharcterType			= PlayerCharacterType::COUNT;
	GameEngineCollision*		CollisionPtr				= nullptr;
	int									lifeCnt						= 39999;

	const float						ProtectionTime		= 3.f;
	float								AliveLiveTime			= ProtectionTime;


	//��Ȱ�� �� ���� ����
	void ProtectionRender();
};

