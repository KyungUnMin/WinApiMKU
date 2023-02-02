#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// ���� :
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineCollision;

class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;
	friend GameEngineCollision;

public:
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;



	template <typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}

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


	//Actors�� Ư�� �׷쿡 �ִ� ������Ʈ���� �ٿ�ĳ���� �Ͽ� �迭�� ��� return�ϴ� �Լ�
	template <typename ConvertType>
	std::vector<ConvertType*> GetConvertActors(int _GroundIndex)
	{
		std::vector<ConvertType*> Result;
		std::list<GameEngineActor*>& Group = Actors[_GroundIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

			if (nullptr == ConvertType)
			{
				MsgAssert("����Ʈ �� �� ���� ��ȯ�Դϴ�");
			}

			Result.push_back(ConvertPtr);
		}

		return Result;
	}


	template <typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroundIndex)
	{
		return GetActors(static_cast<int>(_GroundIndex));
	}


	//Actors�� Ư�� �׷쿡 �ִ� ������Ʈ���� �迭�� ��� return�ϴ� �Լ�
	std::vector<GameEngineActor*> GetActors(int _GroundIndex)
	{
		std::vector<GameEngineActor*> Result;
		std::list<GameEngineActor*>& Group = Actors[_GroundIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			Result.push_back(ActorPtr);
		}

		return Result;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	//������ ��ü�ɶ� ������ �ؾ� �� �۾�
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;

	//������ ��ü�� �� ó���ؾ� �� �۾�
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;


private:
	//ī�޶� ��ġ
	float4 CameraPos = float4::Zero;

	std::map<int, std::list<GameEngineActor*>>		Actors;
	std::map<int, std::list<GameEngineRender*>>	Renders;
	std::map<int, std::list<GameEngineCollision*>>	Collisions;

	//���Ͱ� ������ �� ȣ��(CreateActor)
	void ActorStart(GameEngineActor* _Actor, int _Order);

	//Renders�� GameEngineRender�� ���(GameEngineRender::SetOrder���� ���� ���)
	void PushRender(GameEngineRender* _Render);

	void PushCollision(GameEngineCollision* _Collision);

	//�� ������ �����ϴ� ��� ���͵��� Updateȣ��(Core�� GlobalUpdate���� ȣ��)
	void ActorsUpdate(float _DeltaTime);

	//�� ������ �����ϴ� ��� ���͵��� Renderȣ��(Core�� GlobalUpdate���� ȣ��)
	void ActorsRender(float _DeltaTime);

	//�̹� �����ӿ� Deathó���� Object���� deleteó���ϴ� ���
	void Release();
};

