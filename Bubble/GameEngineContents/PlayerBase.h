#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class GameEngineCollision;
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
	PlayerFSM*						FSMPtr				= nullptr;
	BubbleSpawner*				BBSpawner		= nullptr;

	PlayerCharacterType		CharcterType	= PlayerCharacterType::COUNT;
	GameEngineCollision*		CollisionPtr		= nullptr;
	int									lifeCnt				= 3;

	const float						ProtectionTime = 3.f;
	float								AliveLiveTime = 0.f;

	//���Ϳ��� �浹
	void MonsterCollisionCheck();

	//��Ȱ�� �� ���� ����
	void ProtectionRender();
};

