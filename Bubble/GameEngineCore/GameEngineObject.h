#pragma once


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

	void On()
	{
		ObjectUpdate = true;
	}

	void Off()
	{
		ObjectUpdate = false;
	}

	void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	//�θ���
	void SetOwner(GameEngineObject* _Parent)
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

protected:

private:
	GameEngineObject*	Parent				= nullptr;
	bool								ObjectDeath	= false;
	bool								ObjectUpdate	= true;
};

