#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// 설명 :
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

	//order는 업데이트&렌더링 되는 순서
	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0)
	{
		ActorType* Actor = new ActorType();
		ActorStart(Actor, _Order);
		Actors[_Order].push_back(Actor);
		return Actor;
	}

	//카메라 이동
	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	//카메라 위치 설정
	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	float4 GetCameraPos()
	{
		return CameraPos;
	}


	//Actors의 특정 그룹에 있는 오브젝트들을 다운캐스팅 하여 배열에 담아 return하는 함수
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
				MsgAssert("컨버트 할 수 없는 변환입니다");
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


	//Actors의 특정 그룹에 있는 오브젝트들을 배열에 담아 return하는 함수
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

	//레벨이 교체될때 마무리 해야 할 작업
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;

	//레벨이 교체된 후 처리해야 할 작업
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;


private:
	//카메라 위치
	float4 CameraPos = float4::Zero;

	std::map<int, std::list<GameEngineActor*>>		Actors;
	std::map<int, std::list<GameEngineRender*>>	Renders;
	std::map<int, std::list<GameEngineCollision*>>	Collisions;

	//엑터가 생성될 때 호출(CreateActor)
	void ActorStart(GameEngineActor* _Actor, int _Order);

	//Renders에 GameEngineRender를 등록(GameEngineRender::SetOrder에서 직접 등록)
	void PushRender(GameEngineRender* _Render);

	void PushCollision(GameEngineCollision* _Collision);

	//이 레벨에 존재하는 모든 엑터들의 Update호출(Core의 GlobalUpdate에서 호출)
	void ActorsUpdate(float _DeltaTime);

	//이 레벨에 존재하는 모든 엑터들의 Render호출(Core의 GlobalUpdate에서 호출)
	void ActorsRender(float _DeltaTime);

	//이번 프레임에 Death처리한 Object들을 delete처리하는 기능
	void Release();
};

