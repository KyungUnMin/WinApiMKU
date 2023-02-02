#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class DoorType
{
	Blue		= 0,
	Gold		= 14,
	Green	= 28
};

class GameEngineRender;
class GameEngineCollision;

class NextDoor : public GameEngineActor
{
public:
	static const float4 CollisionScale;
	static const float4 CollisionOffset;

	NextDoor();
	~NextDoor();

	NextDoor(const NextDoor& _Other) = delete;
	NextDoor(NextDoor&& _Other) noexcept = delete;
	NextDoor& operator=(const NextDoor& _Other) = delete;
	NextDoor& operator=(const NextDoor&& _Other) noexcept = delete;

	//���� ���� ���� �� ũ��, ������ ���� ����
	template <typename RenderOrder>
	void SelectDoor(DoorType _DoorType, float4 _Scale, RenderOrder _Order)
	{
		//�� ������ ����
		DoorRender = CreateRender("NextDoor.bmp", static_cast<int>(_Order));

		//ũ�� ����
		SetScale(_Scale);

		//���� ������ ���� �ִϸ��̼� ����
		CreateDoorAni(_DoorType);
	}

	void SetScale(float4 _Scale);

	bool IsOpened()
	{
		return IsOpenedValue;
	}

	//�ʱ� ���·� �ǵ�����
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*		DoorRender			= nullptr;
	GameEngineCollision*		CollisionPtr			= nullptr;

	//���� �̹� ���ȴ��� ����
	bool									IsOpenedValue	= false;

	//�÷��̾�� �浹 �ߴ��� ����
	bool									IsPlayerCollision = false;

	//�� ���� �ִϸ��̼� ����
	void DoorOpen();


	//�� Ŭ���� ���ʷ� ���ҽ� �޾ƿ���
	void ResourceLoad();

	//���� ������ ���� �ִϸ��̼� ����
	void CreateDoorAni(DoorType _SelectedDoor);

	void CollisionPlayer();
	void DoorAnimation();
};

