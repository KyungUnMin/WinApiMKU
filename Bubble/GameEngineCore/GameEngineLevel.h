#pragma once
#include <list>
#include <map>

// 설명 :
class GameEngineCore;
class GameEngineActor;
class GameEngineLevel
{
	friend GameEngineCore;

public:
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	//order는 업데이트&렌더링 되는 순서
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();
		ActorStart(Actor, _Order);
		Actors[_Order].push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

private:
	std::map<int, std::list<GameEngineActor*>> Actors;

	//이 레벨에 존재하는 모든 엑터들의 Update호출(Core의 GlobalUpdate에서 호출)
	void ActorsUpdate();

	//이 레벨에 존재하는 모든 엑터들의 Render호출(Core의 GlobalUpdate에서 호출)
	void ActorsRender();

	//엑터가 생성될 때 호출(CreateActor)
	void ActorStart(GameEngineActor* _Actor, int _Order);
};

