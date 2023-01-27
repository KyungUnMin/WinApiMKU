#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class ComponentBase;

class MovableActor : public GameEngineActor
{
public:
	static const float ColliderRange;
	static const std::string LeftStr;
	static const std::string RightStr;

	MovableActor();
	virtual ~MovableActor() = 0;

	MovableActor(const MovableActor& _Other) = delete;
	MovableActor(MovableActor&& _Other) noexcept = delete;
	MovableActor& operator=(const MovableActor& _Other) = delete;
	MovableActor& operator=(const MovableActor&& _Other) noexcept = delete;



	inline const std::string& GetDirStr()
	{
		return Dir;
	}

	const float4& GetDirVec();

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
	float			GravityAcc		= 0.0f;

	void CheckDirection();
};

