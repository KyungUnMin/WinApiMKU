#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// 설명 :
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

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	//레벨이 교체될때 마무리 해야 할 작업
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;

	//레벨이 교체된 후 처리해야 할 작업
	virtual void LevelChangeStart(GameEngineLevel* _NextLevel) = 0;


private:
	//카메라 위치
	float4 CameraPos = float4::Zero;

	std::map<int, std::list<GameEngineActor*>>		Actors;
	std::map<int, std::list<GameEngineRender*>>	Renders;

	//이 레벨에 존재하는 모든 엑터들의 Update호출(Core의 GlobalUpdate에서 호출)
	void ActorsUpdate(float _DeltaTime);

	//이 레벨에 존재하는 모든 엑터들의 Render호출(Core의 GlobalUpdate에서 호출)
	void ActorsRender(float _DeltaTime);

	//엑터가 생성될 때 호출(CreateActor)
	void ActorStart(GameEngineActor* _Actor, int _Order);

	//Renders에 GameEngineRender를 등록(GameEngineRender::SetOrder에서 직접 호출)
	void PushRender(GameEngineRender* _Render);
};

