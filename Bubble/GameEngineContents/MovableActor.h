#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class ComponentBase;

//계산을 통해 움직이는 Actor는 이 클래스를 상속
class MovableActor : public GameEngineActor
{
public:
	//레벨의 Obstacle과 충돌처리를 할 때 자신의 충돌 범위(추후 클래스의 멤버변수로 종속시킬 예정)
	static const float ColliderRange;

	static const std::string LeftStr;
	static const std::string RightStr;

	MovableActor();
	virtual ~MovableActor() = 0;

	MovableActor(const MovableActor& _Other) = delete;
	MovableActor(MovableActor&& _Other) noexcept = delete;
	MovableActor& operator=(const MovableActor& _Other) = delete;
	MovableActor& operator=(const MovableActor&& _Other) noexcept = delete;


	//이 물체가 현재 바라보고 있는 방향을 string으로 반환
	inline const std::string& GetDirStr()
	{
		return Dir;
	}

	//이 물체가 현재 바라보고 있는 방향을 float4(벡터)로 반환
	const float4& GetDirVec();

	//이번 프레임에서 이 클래스의 방향이 바뀌였는지 여부반환
	inline bool IsDirChanged()
	{
		return DirChanged;
	}


	inline float4 GetAcceleration()
	{
		return Acceleration;
	}

	inline void SetAcceleration(float4 _Acc)
	{
		Acceleration = _Acc;
	}

	inline void SetMoveAcceleration(float4 _Acc)
	{
		Acceleration += _Acc;
	}

	inline void SetGravityAcceleration(float _Y)
	{
		Acceleration.y = _Y;
	}

	void SetDir(const float4& _Dir);


protected:
	//이번 프레임에 방향이 바뀌였는지 체크
	virtual void CheckDirection();

private:
	std::string	Dir					= MovableActor::RightStr;
	bool				DirChanged		= false;

	//물체의 가속도
	float4			Acceleration	= float4::Zero;

	
};

