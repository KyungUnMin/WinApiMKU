#pragma once
#include <map>
#include "MovableActor.h"
#include "ContentsEnum.h"

class ComponentBase;
class GameEngineCollision;

//��� �÷��̾� Ŭ������ �θ� �Ǵ� �߻� Ŭ����
class PlayerBase : public MovableActor
{
public:
	static const float4 CollisionOffset;
	static const float4 CollisionScale;
	static int TestCnt;

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

	bool DecreaseLife()
	{
		--lifeCnt;
		return 0 < lifeCnt;
	}

protected:
	//�÷��̾ ����� ������Ʈ�� ����� �ʱ�ȭ
	void Start() override;

	//������ üũ�ϰ� ������Ʈ���� ����
	void Update(float _DeltaTime) final;

private:
	//������Ʈ ������ ����
	std::map<ComponentType,ComponentBase*>	Components;

	GameEngineCollision*		CollisionPtr		= nullptr;
	int									lifeCnt				= 3;

	int test = TestCnt++;
};

