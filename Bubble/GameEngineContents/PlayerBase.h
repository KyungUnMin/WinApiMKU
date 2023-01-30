#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class ComponentBase;

//��� �÷��̾� Ŭ������ �θ� �Ǵ� �߻� Ŭ����
class PlayerBase : public MovableActor
{
public:
	PlayerBase();
	virtual ~PlayerBase() = 0;

	PlayerBase(const PlayerBase& _Other) = delete;
	PlayerBase(PlayerBase&& _Other) noexcept = delete;
	PlayerBase& operator=(const PlayerBase& _Other) = delete;
	PlayerBase& operator=(const PlayerBase&& _Other) noexcept = delete;

	//������Ʈ�� ����ִ� �ڷᱸ������ �ش� ������Ʈ�� ã�� ��ȯ
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
	//�÷��̾ ����� ������Ʈ�� ����� �ʱ�ȭ
	void Start() override;

	//������ üũ�ϰ� ������Ʈ���� ����
	void Update(float _DeltaTime) final;

private:
	//������Ʈ ������ ����
	std::map<ComponentType,ComponentBase*>	Components;
};

