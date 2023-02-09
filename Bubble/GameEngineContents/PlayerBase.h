#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class GameEngineCollision;
class PlayerFSM;
class BubbleSpawner;
class Gravity;

//��� �÷��̾� Ŭ������ �θ� �Ǵ� �߻� Ŭ����
class PlayerBase : public MovableActor
{
public:
	static const float4 CollisionOffset;
	static const float4 CollisionScale;

	PlayerBase();
	virtual ~PlayerBase() = 0;

	PlayerBase(const PlayerBase& _Other) = delete;
	PlayerBase(PlayerBase&& _Other) noexcept = delete;
	PlayerBase& operator=(const PlayerBase& _Other) = delete;
	PlayerBase& operator=(const PlayerBase&& _Other) noexcept = delete;

	bool DecreaseLife()
	{
		--lifeCnt;
		return 0 < lifeCnt;
	}

	PlayerCharacterType GetCharacterType();

	inline  PlayerFSM* GetFSM()
	{
		return FsmPtr;
	}

	inline Gravity* GetGravity()
	{
		return GravityPtr;
	}

protected:
	//�÷��̾ ����� ������Ʈ�� ����� �ʱ�ȭ
	void Start() override;

	//������ üũ�ϰ� ������Ʈ���� ����
	void Update(float _DeltaTime) final;

	inline void SetCharacterType(PlayerCharacterType _Type)
	{
		CharcterType = _Type;
	}

private:
	PlayerFSM*						FsmPtr				= nullptr;
	BubbleSpawner*				BBSpawner		= nullptr;
	Gravity*							GravityPtr		= nullptr;

	PlayerCharacterType		CharcterType	= PlayerCharacterType::COUNT;
	GameEngineCollision*		CollisionPtr		= nullptr;
	int									lifeCnt				= 3;



	void BubbleCollisionCheck();
};

