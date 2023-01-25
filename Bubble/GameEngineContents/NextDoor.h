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

	template <typename RenderOrder>
	void SelectDoor(DoorType _DoorColor, float4 _Scale, RenderOrder _Order)
	{
		DoorRender = CreateRender("NextDoor.bmp", static_cast<int>(_Order));
		SetScale(_Scale);
		CreateDoorAni(_DoorColor);
	}

	void SetScale(float4 _Scale);

	void DoorOpen();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*	DoorRender		= nullptr;
	bool								IsOpened			= false;

	void ResourceLoad();
	void CreateDoorAni(DoorType _SelectedDoor);
};

