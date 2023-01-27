#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class ComponentBase;

class PlayerBase : public GameEngineActor
{
public:
	PlayerBase();
	virtual ~PlayerBase() = 0;

	PlayerBase(const PlayerBase& _Other) = delete;
	PlayerBase(PlayerBase&& _Other) noexcept = delete;
	PlayerBase& operator=(const PlayerBase& _Other) = delete;
	PlayerBase& operator=(const PlayerBase&& _Other) noexcept = delete;

	inline const std::string& GetDirStr()
	{
		return Dir;
	}

	const float4& GetDirVec();

	inline bool IsDirChanged()
	{
		return DirChanged;
	}

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
	void Start() override;
	void Update(float _DeltaTime) final;

private:
	std::map<ComponentType,ComponentBase*>	Components;

	std::string									Dir					= "Right_";
	bool												DirChanged		= false;

	void CheckDirection();
};

