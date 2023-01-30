#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class ComponentBase;

//모든 플레이어 클래스의 부모가 되는 추상 클래스
class PlayerBase : public MovableActor
{
public:
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


protected:
	//플레이어가 사용할 컴포넌트를 만들고 초기화
	void Start() override;

	//방향을 체크하고 컴포넌트들을 동작
	void Update(float _DeltaTime) final;

private:
	//컴포넌트 구조로 동작
	std::map<ComponentType,ComponentBase*>	Components;
};

