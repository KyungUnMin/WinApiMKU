#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class GameEngineCollision;
class PlayerFSM;
class BubbleSpawner;

//모든 플레이어 클래스의 부모가 되는 추상 클래스
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
	//플레이어가 사용할 컴포넌트를 만들고 초기화
	void Start() override;

	//방향을 체크하고 컴포넌트들을 동작
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

	//몬스터와의 충돌
	void MonsterCollisionCheck();

	//부활한 뒤 무적 연출
	void ProtectionRender();
};

