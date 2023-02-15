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

	//virtual인 이유는 이를 상속받는 클래스에 따라 추가 작업을 처리하기 위함
	virtual void SetOrder(int _Order)
	{
		//Actor의 경우 Update되는 순서
		//Render의 경우 이미지가 그려지는 순서
		//Collision의 경우 충돌되는 순서(그룹)

		Order = _Order;
	}
	
	int GetOrder()
	{
		return Order;
	}


	//부모설정
	virtual void SetOwner(GameEngineObject* _Parent)
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

