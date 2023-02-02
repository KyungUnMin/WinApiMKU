#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class ComponentBase;
class GameEngineCollision;

//모든 플레이어 클래스의 부모가 되는 추상 클래스
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

	//컴포넌트를 담고있는 자료구조에서 해당 컴포넌트를 찾아 반환
	template <typename T>
	T* GetComponent(ComponentType _Type)
	{
		auto Iter = Components.find(_Type);
		if (Components.end() == Iter)
		{
			return nullptr;
		}

		T* Return = dynamic_cast<T*>(Iter->second);
		return Return;
	}

	bool DecreaseLife()
	{
		--lifeCnt;
		return 0 < lifeCnt;
	}

	PlayerCharacterType GetCharacterType();


protected:
	//플레이어가 사용할 컴포넌트를 만들고 초기화
	void Start() override;

	//방향을 체크하고 컴포넌트들을 동작
	void Update(float _DeltaTime) final;

	inline void SetCharacterType(PlayerCharacterType _Type)
	{
		CharcterType = _Type;
	}

private:
	//컴포넌트 구조로 동작
	std::map<ComponentType,ComponentBase*>	Components;

	PlayerCharacterType		CharcterType	= PlayerCharacterType::COUNT;
	GameEngineCollision*		CollisionPtr		= nullptr;
	int									lifeCnt				= 3;
};

