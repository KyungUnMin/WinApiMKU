#pragma once
#include <string>
#include <string_view>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

class BackGround;
class GameEngineImage;
class PlayerBase;

//���� ������ �����ϴ� ������ �� Ŭ������ ��ӹ޴´�
//RoundLevel�� �Ϸķ� ���ĵ� Render�� ���� �ִ´�.(�� Render�� Stage�� �ǹ�, ex : RoundA_Stage01)
class RoundLevelBase : public GameEngineLevel
{
public:
	RoundLevelBase();
	virtual ~RoundLevelBase() = 0;

	RoundLevelBase(const RoundLevelBase& _Other) = delete;
	RoundLevelBase(RoundLevelBase&& _Other) noexcept = delete;
	RoundLevelBase& operator=(const RoundLevelBase& _Other) = delete;
	RoundLevelBase& operator=(const RoundLevelBase&& _Other) noexcept = delete;

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

protected:
	void Loading() override{}
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override{}

	//������ ������ �浹ü�� �ε��ϴ� �Լ�
	void LoadObstacle(const std::string_view& _RoundName, int _X, int _Y);

	//������ ������ �����ϴ� �Լ�
	template <typename RenderOrder>
	void CreateObstacle(const float4& _ArrangeDir, RenderOrder _Order)
	{
		CreateObstacle(_ArrangeDir, static_cast<int>(_Order));
	}
	void CreateObstacle(const float4& _ArrangeDir, int _Order);

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

	//_CenterIndex�� �������� ��� _Dir �������� Stage���� ����
	void ArrangeStage(float4 _Dir, size_t _CenterIndex);

private:
	//������ ĳ���� Ÿ��
	PlayerCharacterType	SelectedCharacter	= PlayerCharacterType::BOBBLUN;
	PlayerBase*					Player						= nullptr;

	//Obstacle�� �����ϴµ� ����ϴ� ����
	std::string					ImageName				= "Round";
	BackGround*				Obstacles				= nullptr;
	GameEngineImage*		ColliderImage			= nullptr;


	//IsMoveValue�� true�϶� Update���� Stage�� �̵���
	bool								IsMoveValue			= false;
	size_t							NowIndex				= 0;
	float4							MoveDir					= float4::Zero;
	const float					MoveSpeed				= 500.f;
};

