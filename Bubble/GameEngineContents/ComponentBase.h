#pragma once



class GameEngineActor;

class ComponentBase
{
public:
	ComponentBase();
	virtual ~ComponentBase() = 0;

	ComponentBase(const ComponentBase& _Other) = delete;
	ComponentBase(ComponentBase&& _Other) noexcept = delete;
	ComponentBase& operator=(const ComponentBase& _Other) = delete;
	ComponentBase& operator=(const ComponentBase&& _Other) noexcept = delete;

	inline void SetOwner(GameEngineActor* _Owner)
	{
		Owner = _Owner;
	}

	inline GameEngineActor* GetOwner()
	{
		return Owner;
	}

	virtual void Start() {}
	virtual void Update(float _DeltaTime){}

protected:

private:
	GameEngineActor* Owner = nullptr;
};

