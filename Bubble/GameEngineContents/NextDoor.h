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

	//문의 종류 선택 및 크기, 렌더링 순서 결정
	template <typename RenderOrder>
	void SelectDoor(DoorType _DoorType, float4 _Scale, RenderOrder _Order)
	{
		//문 렌더링 생성
		DoorRender = CreateRender("NextDoor.bmp", static_cast<int>(_Order));

		//크기 설정
		SetScale(_Scale);

		//문의 종류에 따라 애니메이션 지정
		CreateDoorAni(_DoorType);
	}

	void SetScale(float4 _Scale);

	bool IsOpened()
	{
		return IsOpenedValue;
	}

	//초기 상태로 되돌리기
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender*		DoorRender			= nullptr;

	//문이 이미 열렸는지 여부
	bool									IsOpenedValue	= false;

	//플레이어와 충돌 했는지 여부
	bool									IsPlayerCollision = false;

	//문이 생성되고 난 시간
	float								CreateLiveTime	= 0.f;

	//플레이어와 충돌을 허락할 시간
	const float						CollisionOkTime	= 2.f;

	//플레이어와 문이 충돌했을때 플레이어 위치
	float4								PlayerColPos		= float4::Zero;

	//플레이어와 충돌한 시간
	float								ColisionTime		= 0.f;

	const float						MoveDuration = 1.f;

	//문 열기 애니메이션 실행
	void DoorOpen();


	//이 클래스 최초로 리소스 받아오기
	void ResourceLoad();

	//문의 종류에 따라 애니메이션 지정
	void CreateDoorAni(DoorType _SelectedDoor);

	void CollisionPlayer();
	void DoorAnimation();
	void MovePlayer();
};

