#pragma once

class GameEngineActor;

//��� ������Ʈ�� ���̽��� �Ǵ� Ŭ����
class ComponentBase
{
public:
	ComponentBase();
	virtual ~ComponentBase() = 0;

	ComponentBase(const ComponentBase& _Other) = delete;
	ComponentBase(ComponentBase&& _Other) noexcept = delete;
	ComponentBase& operator=(const ComponentBase& _Other) = delete;
	ComponentBase& operator=(const ComponentBase&& _Other) noexcept = delete;

	//�� ������Ʈ�� ���� �ִ� ����actor ����
	inline void SetOwner(GameEngineActor* _Owner)
	{
		Owner = _Owner;
	}

	//�� ������Ʈ�� ���� �ִ� ����actor ��ȯ
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

