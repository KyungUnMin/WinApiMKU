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
		부모가 존재한다면
			ObjectUpdate가 true면서
			ObjectDeath는 false여야하며
			부모도 마찬가지일 때
			true 리턴
		부모가 존재하지 않는다면
			ObjectUpdate가 true면서
			ObjectDeath는 false일때
			true 리턴
		*/
		return (nullptr != Parent) ? (ObjectUpdate && false == ObjectDeath && Parent->IsUpdate()) : (ObjectUpdate && false == ObjectDeath);
	}

	bool IsDeath()
	{
		/*
		부모가 존재한다면
			ObjectDeath가 true거나
			부모가 죽었을때
			true 리턴
		부모가 존재하지 않는다면
			ObjectDeath 리턴
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

	//부모설정
	void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	//부모를 캐스팅하여 포인터 주기
	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	//부모 포인터 주기
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

