#pragma once
#include "NatureMissleBase.h"

class NatureMissle_Windy : public NatureMissleBase
{
public:
	static const std::string_view ImagePath;
	static const std::string_view AniName;

	NatureMissle_Windy();
	~NatureMissle_Windy() override;

	NatureMissle_Windy(const NatureMissle_Windy& _Other) = delete;
	NatureMissle_Windy(NatureMissle_Windy&& _Other) noexcept = delete;
	NatureMissle_Windy& operator=(const NatureMissle_Windy& _Other) = delete;
	NatureMissle_Windy& operator=(const NatureMissle_Windy&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4								DestPos				= float4::Zero;

	bool									IsHorizonMove	= false;
	float4								Dir						= float4::Zero;
	float								DirChangeTime	= 0.f;
	float								MoveAccTime		= 0.f;
	const float						MoveSpeed			= 400.f;

	std::list<MonsterBase*>	DragMonsters;
	

	void ResourceLoad();
	void CreateAnimation();
	void ChangeDirection();

	void Move(float _DeltaTime);
	bool ScreenOutCheck();

	void MonsterKill();
	void MonsterDrag();
};

