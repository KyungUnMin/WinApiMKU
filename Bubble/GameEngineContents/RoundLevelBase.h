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

//���� ������ �����ϴ� ������ �� Ŭ������ ��ӹ޴´�
//RoundLevel�� �Ϸķ� ���ĵ� Render�� ���� �ִ´�.(�� Render�� Stage�� �ǹ�, ex : RoundA_Stage01)
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

	//NowIndex�� ���� Round���� ������ Stage���� �˷��ִ� �Լ�
	bool IsLastStage();

	//���ڷ� �޴� _Pos�� ������ ������ ���� ���� ������ �˷��ִ� �Լ�
	bool IsBlockPos(const float4& _Pos);



	//���� Round���� ���õ� ĳ���� Ÿ���� ��ȯ
	inline PlayerCharacterType GetSelectCharacter()
	{
		return SelectedCharacter;
	}

	//(�ַ� RoundLevelBase�� ��ӹ��� �ٸ� �������� LevelChangeEnd or LevelChangeStart�� ���� ȣ���)
	//���� Round�� ĳ���� Ÿ���� ����
	inline void SetCharacter(PlayerCharacterType _Type)
	{
		SelectedCharacter = _Type;
	}



	inline bool IsMoving()
	{
		return IsMoveValue;
	}

	//���� Round�� Stage�� ������ �����ϴ� �Լ�
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

	//������ ������ �浹ü�� �ε��ϴ� �Լ�
	void LoadStage(const std::string_view& _RoundName, int _X, int _Y);

	//������ ������ �����ϴ� �Լ�
	template <typename RenderOrder>
	void CreateStage(const float4& _ArrangeDir, RenderOrder _Order)
	{
		CreateStage(_ArrangeDir, static_cast<int>(_Order));
	}
	void CreateStage(const float4& _ArrangeDir, int _Order);

	//���� Stage�� �̵��ϴ� �Լ�
	bool MoveToNextStage();


	//(�ַ� RoundLevelBase�� ��ӹ��� �ٸ� �������� LevelChangeEnd or LevelChangeStart�� ���� ȣ���)
	//�÷��̾ �����ϴ� �Լ�
	void CreatePlayer(PlayerCharacterType _Type);

	
	//CreatePlayer���� ����� �÷��̾ return
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
	//������ ĳ���� Ÿ��
	PlayerCharacterType					SelectedCharacter	= PlayerCharacterType::BUBBLUN;
	PlayerBase*									Player						= nullptr;

	//Obstacle�� �����ϴµ� ����ϴ� ����
	std::string									ImageName				= "Round";
	BackGround*								StageImage				= nullptr;
	GameEngineImage*						StageCollision			= nullptr;


	//IsMoveValue�� true�϶� Update���� Stage�� �̵���
	bool												IsMoveValue			= false;
	size_t											NowStageIndex		= 0;
	float4											ArrangeDir				= float4::Zero;
	float											StageMoveTime		= 0.f;

	//BubbleDestination�� ���õ� ����Ŭ����
	BubbleDestHelper*						DestHelperPtr			= nullptr;

	GameEngineSoundPlayer			BGMPlayer;
	const std::string_view				RoundBgmName		= "RoundBGM.mp3";

	std::vector<MonsterSpawner*>	MonsterSpawners;
	PointPannel*								ScorePannel				= nullptr;

	void CreateSpanwerPool(int _StageCount);
	void BgmLoad();
	void StageClear();
};

