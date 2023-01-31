#pragma once
#include <string>
#include <string_view>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

class BackGround;
class GameEngineImage;
class PlayerBase;

//실제 게임이 동작하는 레벨은 이 클래스를 상속받는다
//RoundLevel은 일렬로 정렬된 Render를 갖고 있는다.(이 Render는 Stage를 의미, ex : RoundA_Stage01)
class RoundLevelBase : public GameEngineLevel
{
public:
	RoundLevelBase();
	virtual ~RoundLevelBase() = 0;

	RoundLevelBase(const RoundLevelBase& _Other) = delete;
	RoundLevelBase(RoundLevelBase&& _Other) noexcept = delete;
	RoundLevelBase& operator=(const RoundLevelBase& _Other) = delete;
	RoundLevelBase& operator=(const RoundLevelBase&& _Other) noexcept = delete;

	//NowIndex가 현재 Round에서 마지막 Stage인지 알려주는 함수
	bool IsLastStage();

	//인자로 받는 _Pos가 레벨의 지형에 의해 막힌 곳인지 알려주는 함수
	bool IsBlockPos(const float4& _Pos);

	//현재 Round에서 선택된 캐릭터 타입을 반환
	inline PlayerCharacterType GetSelectCharacter()
	{
		return SelectedCharacter;
	}

	//(주로 RoundLevelBase를 상속받은 다른 레벨에서 LevelChangeEnd or LevelChangeStart를 통해 호출됨)
	//현재 Round의 캐릭터 타입을 선택
	inline void SetCharacter(PlayerCharacterType _Type)
	{
		SelectedCharacter = _Type;
	}

	inline bool IsMoving()
	{
		return IsMoveValue;
	}

protected:
	void Loading() override{}
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override{}

	//레벨의 지형과 충돌체를 로드하는 함수
	void LoadObstacle(const std::string_view& _RoundName, int _X, int _Y);

	//레벨의 지형을 생성하는 함수
	template <typename RenderOrder>
	void CreateObstacle(const float4& _ArrangeDir, RenderOrder _Order)
	{
		CreateObstacle(_ArrangeDir, static_cast<int>(_Order));
	}
	void CreateObstacle(const float4& _ArrangeDir, int _Order);

	//다음 Stage로 이동하는 함수
	bool MoveToNextStage();


	//(주로 RoundLevelBase를 상속받은 다른 레벨에서 LevelChangeEnd or LevelChangeStart를 통해 호출됨)
	//플레이어를 생성하는 함수
	void CreatePlayer(PlayerCharacterType _Type);

	
	//CreatePlayer에서 등록한 플레이어를 return
	inline PlayerBase* GetPlayer()
	{
		return Player;
	}

	//_CenterIndex를 기준으로 삼고 _Dir 방향으로 Stage들을 정렬
	void ArrangeStage(float4 _Dir, size_t _CenterIndex);

private:
	//선택한 캐릭터 타입
	PlayerCharacterType	SelectedCharacter	= PlayerCharacterType::BOBBLUN;
	PlayerBase*					Player						= nullptr;

	//Obstacle을 생성하는데 사용하는 변수
	std::string					ImageName				= "Round";
	BackGround*				Obstacles				= nullptr;
	GameEngineImage*		ColliderImage			= nullptr;


	//IsMoveValue이 true일때 Update에서 Stage가 이동함
	bool								IsMoveValue			= false;
	size_t							NowIndex				= 0;
	float4							MoveDir					= float4::Zero;
	const float					MoveSpeed				= 500.f;
};

