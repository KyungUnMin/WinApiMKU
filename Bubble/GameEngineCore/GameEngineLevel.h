#pragma once
#include <list>
#include <map>

// ���� :
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;

class GameEngineLevel
{
	friend GameEngineCore;
	friend GameEngineRender;

public:
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	//order�� ������Ʈ&������ �Ǵ� ����
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();
		ActorStart(Actor, _Order);
		Actors[_Order].push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	//������ ��ü�ɶ� ������ �ؾ� �� �۾�
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;

	//������ ��ü�� �� ó���ؾ� �� �۾�
	virtual void LevelChangeStart(GameEngineLevel* _NextLevel) = 0;


private:
	std::map<int, std::list<GameEngineActor*>>		Actors;
	std::map<int, std::list<GameEngineRender*>>	Renders;

	//�� ������ �����ϴ� ��� ���͵��� Updateȣ��(Core�� GlobalUpdate���� ȣ��)
	void ActorsUpdate(float _DeltaTime);

	//�� ������ �����ϴ� ��� ���͵��� Renderȣ��(Core�� GlobalUpdate���� ȣ��)
	void ActorsRender(float _DeltaTime);

	//���Ͱ� ������ �� ȣ��(CreateActor)
	void ActorStart(GameEngineActor* _Actor, int _Order);

	//Renders�� GameEngineRender�� ���(GameEngineRender::SetOrder���� ���� ȣ��)
	void PushRender(GameEngineRender* _Render);
};

