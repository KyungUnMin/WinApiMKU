#pragma once
#include <string>
#include <string_view>

class GameEngineObject
{
public:
	GameEngineObject();
	virtual ~GameEngineObject();

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(const GameEngineObject&& _Other) noexcept = delete;

	bool IsUpdate()
	{
		/*
		�θ� �����Ѵٸ�
			ObjectUpdate�� true�鼭
			ObjectDeath�� false�����ϸ�
			�θ� ���������� ��
			true ����
		�θ� �������� �ʴ´ٸ�
			ObjectUpdate�� true�鼭
			ObjectDeath�� false�϶�
			true ����
		*/
		return (nullptr != Parent) ? (ObjectUpdate && false == ObjectDeath && Parent->IsUpdate()) : (ObjectUpdate && false == ObjectDeath);
	}

	bool IsDeath()
	{
		/*
		�θ� �����Ѵٸ�
			ObjectDeath�� true�ų�
			�θ� �׾�����
			true ����
		�θ� �������� �ʴ´ٸ�
			ObjectDeath ����
		*/
		return (nullptr != Parent) ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

	void Death()
	{
		ObjectDeath = true;
	}

	virtual void On()
	{
		ObjectUpdate = true;
	}

	virtual void Off()
	{
		ObjectUpdate = false;
	}

	virtual void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	//virtual�� ������ �̸� ��ӹ޴� Ŭ������ ���� �߰� �۾��� ó���ϱ� ����
	virtual void SetOrder(int _Order)
	{
		//Actor�� ��� Update�Ǵ� ����
		//Render�� ��� �̹����� �׷����� ����
		//Collision�� ��� �浹�Ǵ� ����(�׷�)

		Order = _Order;
	}
	
	int GetOrder()
	{
		return Order;
	}


	//�θ���
	virtual void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	//�θ� ĳ�����Ͽ� ������ �ֱ�
	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	//�θ� ������ �ֱ�
	GameEngineObject* GetOwner()
	{
		return Parent;
	}

	inline void SetName(const std::string_view& _View)
	{
		Name = _View;
	}

	inline const std::string& GetName()
	{
		return Name;
	}

	inline std::string GetNameCopy()
	{
		return Name;
	}

protected:

private:
	int								Order					= 0;
	GameEngineObject*	Parent					= nullptr;

	bool								ObjectDeath		= false;
	bool								ObjectUpdate		= true;
	std::string					Name;
};

