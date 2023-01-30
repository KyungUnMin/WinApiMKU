#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class ComponentBase;

//계산을 통해 움직이는 Actor는 이 클래스를 상속받습니다
class MovableActor : public GameEngineActor
{
public:
	//레벨의 Obstacle과 충돌처리를 할 때 자신의 충돌 범위(추후 클래스의 멤버변수로 종속시킬수도 있음)
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


	inline float GetGravityAcc()
	{
		return GravityAcc;
	}

	inline void SetGravityAcc(float _Acc)
	{
		GravityAcc = _Acc;
	}

	inline void SetMoveGravityAcc(float _Acc)
	{
		GravityAcc += _Acc;
	}


protected:
	void Update(float _DeltaTime) override;

private:
	std::string	Dir					= MovableActor::RightStr;
	bool				DirChanged		= false;

	//Y축 가속도(중력과 점프에 이용)
	float			GravityAcc		= 0.0f;

	//이번 프레임에 방향이 바뀌였는지 체크
	void CheckDirection();
};

