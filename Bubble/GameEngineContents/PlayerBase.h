#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class GameEngineCollision;
class GameEngineRender;
class PlayerFSM;
class BubbleSpawner;

//모든 플레이어 클래스의 부모가 되는 추상 클래스
class PlayerBase : public MovableActor
{
public:
	static PlayerBase* MainPlayer;

	static const float4 CollisionOffset;
	static const float4 CollisionScale;

	static void UnbeatableSwitch();

	static bool IsUnbeatable()
	{
		return Unbeatable;
	}

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

	inline BubbleSpawner* GetBubbleSpawner()
	{
		return BBSpawner;
	}

	//몬스터쪽에서 호출됨
	void AttackPlayer();

	//FSM의 Damaged State가 빠져나갈때 실행됨
	inline void ResetAliveTime()
	{
		AliveLiveTime = 0.f;
	}

	inline float GetAliveTime()
	{
		return AliveLiveTime;
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
	static bool						Unbeatable;
	GameEngineRender*		ShieldRender			= nullptr;

	const float4					PlayerRenderScale = float4{ 200.f, 200.f };
	GameEngineRender*		RenderPtr				= nullptr;

	PlayerFSM*						FSMPtr						= nullptr;
	BubbleSpawner*				BBSpawner				= nullptr;

	PlayerCharacterType		CharcterType			= PlayerCharacterType::COUNT;
	GameEngineCollision*		CollisionPtr				= nullptr;
	int									lifeCnt						= 39999;

	const float						ProtectionTime		= 3.f;
	float								AliveLiveTime			= ProtectionTime;

	const float						GhostSpawnTime	= 30.f;

	int									RenderAlpha			= 255;

	//부활한 뒤 무적 연출
	void ProtectionRender();
	void CreateCheetShield();
	void CheckStandOnStage();
};

