#pragma once
#include <string>
#include <string_view>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

class BackGround;
class GameEngineImage;
class PlayerBase;

class RoundLevelBase : public GameEngineLevel
{
public:
	RoundLevelBase();
	~RoundLevelBase();

	RoundLevelBase(const RoundLevelBase& _Other) = delete;
	RoundLevelBase(RoundLevelBase&& _Other) noexcept = delete;
	RoundLevelBase& operator=(const RoundLevelBase& _Other) = delete;
	RoundLevelBase& operator=(const RoundLevelBase&& _Other) noexcept = delete;

	bool IsLastStage();

	bool IsBlockPos(const float4& _Pos);


	inline PlayerCharacterType GetSelectCharacter()
	{
		return SelectedCharacter;
	}

	inline void SetCharacter(PlayerCharacterType _Type)
	{
		SelectedCharacter = _Type;
	}

protected:
	void Loading() override{}
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override{}

	void LoadObstacle(const std::string_view& _RoundName, int _X, int _Y);

	template <typename RenderOrder>
	void CreateObstacle(const float4& _ArrangeDir, RenderOrder _Order)
	{
		CreateObstacle(_ArrangeDir, static_cast<int>(_Order));
	}

	void CreateObstacle(const float4& _ArrangeDir, int _Order);

	bool MoveToNextStage();

	void CreatePlayer(PlayerCharacterType _Type);

	inline PlayerBase* GetPlayer()
	{
		return Player;
	}

private:
	PlayerCharacterType	SelectedCharacter	= PlayerCharacterType::BOBBLUN;
	PlayerBase*					Player						= nullptr;

	std::string					ImageName				= "Round";
	BackGround*				Obstacles				= nullptr;
	GameEngineImage*		ColliderImage			= nullptr;

	bool								IsMoving					= false;
	size_t							NowIndex				= 0;
	float4							MoveDir					= float4::Zero;
	const float					MoveSpeed				= 500.f;

	void ArrangeStage(float4 _Dir, size_t _CenterIndex);
};

