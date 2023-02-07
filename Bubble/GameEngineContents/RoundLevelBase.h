#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

class BackGround;
class GameEngineImage;
class PlayerBase;
class BubbleDestination;

//���� ������ �����ϴ� ������ �� Ŭ������ ��ӹ޴´�
//RoundLevel�� �Ϸķ� ���ĵ� Render�� ���� �ִ´�.(�� Render�� Stage�� �ǹ�, ex : RoundA_Stage01)
class RoundLevelBase : public GameEngineLevel
{
public:
	static const float StageMoveDuration;

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

	const float4& GetPlayerSpawnPos();

	void SetPlayerSpawnPos(const std::vector<float4>& _SpawnPos)
	{
		PlayerSpwanPos = _SpawnPos;
	}


	//���� Round�� Stage�� ������ �����ϴ� �Լ�
	void SetNowStage(size_t _StageNum);

	inline float GetStageMoveTime()
	{
		return StageMoveTime;
	}

	const std::vector<BubbleDestination*>& GetBubbleDest(size_t _Stage);

protected:
	void Loading() override{}
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

	void SetBubbleDest(const std::vector<std::vector<float4>>& _LevelBubbleDests);

	void ConnectDestToDest(size_t _Stage, size_t _Start, size_t _End);

private:
	//������ ĳ���� Ÿ��
	PlayerCharacterType	SelectedCharacter	= PlayerCharacterType::BUBBLUN;
	PlayerBase*					Player						= nullptr;
	std::vector<float4>		PlayerSpwanPos;

	//Obstacle�� �����ϴµ� ����ϴ� ����
	std::string					ImageName				= "Round";
	BackGround*				StageImage				= nullptr;
	GameEngineImage*		StageCollision			= nullptr;


	//IsMoveValue�� true�϶� Update���� Stage�� �̵���
	bool								IsMoveValue			= false;
	size_t							NowStageIndex		= 0;
	float4							ArrangeDir				= float4::Zero;
	float							StageMoveTime		= 0.f;

	std::vector<std::vector<BubbleDestination*>> BubbleDests;
	
	void TurnOnBubbleDestOnlyNowStage();
};

