#pragma once

class GameEngineActor;

//모든 컴포넌트의 베이스가 되는 클래스
class ComponentBase
{
public:
	ComponentBase();
	virtual ~ComponentBase() = 0;

	ComponentBase(const ComponentBase& _Other) = delete;
	ComponentBase(ComponentBase&& _Other) noexcept = delete;
	ComponentBase& operator=(const ComponentBase& _Other) = delete;
	ComponentBase& operator=(const ComponentBase&& _Other) noexcept = delete;

	//이 컴포넌트를 갖고 있는 주인actor 설정
	inline void SetOwner(GameEngineActor* _Owner)
	{
		Owner = _Owner;
	}

	//이 컴포넌트를 갖고 있는 주인actor 반환
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

