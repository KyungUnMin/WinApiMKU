#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// ���� :
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;

class GameEngineLevel : public GameEngineObject
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
	ActorType* CreateActor(int _Order = 0)
	{
		ActorType* Actor = new ActorType();
		ActorStart(Actor, _Order);
		Actors[_Order].push_back(Actor);
		return Actor;
	}

	//ī�޶� �̵�
	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	//ī�޶� ��ġ ����
	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	float4 GetCameraPos()
	{
		return CameraPos;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	//������ ��ü�ɶ� ������ �ؾ� �� �۾�
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;

	//������ ��ü�� �� ó���ؾ� �� �۾�
	virtual void LevelChangeStart(GameEngineLevel* _NextLevel) = 0;


private:
	//ī�޶� ��ġ
	float4 CameraPos = float4::Zero;

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

