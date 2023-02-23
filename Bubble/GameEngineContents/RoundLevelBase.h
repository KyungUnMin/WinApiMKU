#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsEnum.h"

class BackGround;
class GameEngineImage;
class PlayerBase;
class BubbleDestHelper;
class MonsterSpawner;
class PointPannel;
class MonsterBase;

//실제 게임이 동작하는 레벨은 이 클래스를 상속받는다
//RoundLevel은 일렬로 정렬된 Render를 갖고 있는다.(이 Render는 Stage를 의미, ex : RoundA_Stage01)
class RoundLevelBase : public GameEngineLevel
{
public:
	static const float4		PlayerSpawnPos;
	static const float		StageMoveDuration;

	RoundLevelBase();
	virtual ~RoundLevelBase() = 0;

	RoundLevelBase(const RoundLevelBase& _Other) = delete;
	RoundLevelBase(RoundLevelBase&& _Other) noexcept = delete;
	RoundLevelBase& operator=(const RoundLevelBase& _Other) = delete;
	RoundLevelBase& operator=(const RoundLevelBase&& _Other) noexcept = delete;

	inline size_t GetNowStage()
	{
		return NowStageIndex;
	}

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

	//현재 Round의 Stage를 강제로 설정하는 함수
	void SetNowStage(size_t _StageNum);

	inline float GetStageMoveTime()
	{
		return StageMoveTime;
	}

	inline BubbleDestHelper* GetBubbleDestHelper()
	{
		return DestHelperPtr;
	}

	std::vector<GameEngineActor*> GetAliveMonsters();

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	//레벨의 지형과 충돌체를 로드하는 함수
	void LoadStage(const std::string_view& _RoundName, int _X, int _Y);

	//레벨의 지형을 생성하는 함수
	template <typename RenderOrder>
	void CreateStage(const float4& _ArrangeDir, RenderOrder _Order)
	{
		CreateStage(_ArrangeDir, static_cast<int>(_Order));
	}
	void CreateStage(const float4& _ArrangeDir, int _Order);

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

	inline MonsterSpawner* GetMonsterSpawner(size_t _StageNum)
	{
		return MonsterSpawners[_StageNum];
	}

	virtual void ChangeNextLevel(){}

private:
	//선택한 캐릭터 타입
	PlayerCharacterType					SelectedCharacter	= PlayerCharacterType::BUBBLUN;
	PlayerBase*									Player						= nullptr;

	//Obstacle을 생성하는데 사용하는 변수
	std::string									ImageName				= "Round";
	BackGround*								StageImage				= nullptr;
	GameEngineImage*						StageCollision			= nullptr;


	//IsMoveValue이 true일때 Update에서 Stage가 이동함
	bool												IsMoveValue			= false;
	size_t											NowStageIndex		= 0;
	float4											ArrangeDir				= float4::Zero;
	float											StageMoveTime		= 0.f;

	//BubbleDestination에 관련된 헬퍼클래스
	BubbleDestHelper*						DestHelperPtr			= nullptr;

	GameEngineSoundPlayer			BGMPlayer;
	const std::string_view				RoundBgmName		= "RoundBGM.mp3";

	std::vector<MonsterSpawner*>	MonsterSpawners;
	PointPannel*								ScorePannel				= nullptr;

	void CreateSpanwerPool(int _StageCount);
	void BgmLoad();
	void StageClear();
};

