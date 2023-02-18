#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class RoundLevelBase;

//계산을 통해 움직이는 Actor는 이 클래스를 상속
class MovableActor : public GameEngineActor
{
public:
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

	virtual void SetDir(const float4& _Dir);

	//내 바로 아래가 땅인지 확인
	bool IsGround(const float4& _CollisionScale);

	bool MoveHorizon(float _Speed, const float4& _CollisionScale, float _DeltaTime);

	void RaiseOnGround(const float4& _CollisionScale);

	void SetReverseDir();

protected:
	void Start() override;

	//이번 프레임에 방향이 바뀌였는지 체크
	void Update(float _DeltaTime) override;

	//void Render(float _DeltaTime) override{}

	RoundLevelBase* GetRoundLevel();

private:
	std::string				Dir					= MovableActor::RightStr;
	bool							DirChanged		= false;
	RoundLevelBase*	RoundLevel		= nullptr;
};

