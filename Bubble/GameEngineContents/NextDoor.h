#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class DoorType
{
	Blue		= 0,
	Gold		= 14,
	Green	= 28
};

class GameEngineRender;

class NextDoor : public GameEngineActor
{
public:
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

	//�� ���� �ִϸ��̼� ����
	void DoorOpen();

	//�ʱ� ���·� �ǵ�����
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*	DoorRender		= nullptr;

	//���� �̹� ���ȴ��� ����
	bool								IsOpened			= false;


	//�� Ŭ���� ���ʷ� ���ҽ� �޾ƿ���
	void ResourceLoad();

	//���� ������ ���� �ִϸ��̼� ����
	void CreateDoorAni(DoorType _SelectedDoor);
};

