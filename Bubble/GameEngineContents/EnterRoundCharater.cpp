#include "EnterRoundCharater.h"
#include <math.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRender.h>
#include "EnterRoundLevel.h"



EnterRoundCharater::EnterRoundCharater()
{

}

EnterRoundCharater::~EnterRoundCharater()
{

}

void EnterRoundCharater::Start()
{
	//캐릭터의 뒤쪽에 존재할 투명 거품 애니메이션 생성 및 재생
	BubbleRender = CreateRender("EnterRoundLevel_ClearBubble.bmp", EnterRoundRenderOrder::PlayerBubble);
	BubbleRender->CreateAnimation
	({
		.AnimationName = "Bubble",
		.ImageName = "EnterRoundLevel_ClearBubble.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.15f
	});

	BubbleRender->SetScale({ 200.f, 200.f });
	BubbleRender->ChangeAnimation("Bubble");
}

//인자로 받은 캐릭터 타입에 따른 애니메이션 생성 및 재생
void EnterRoundCharater::SetCharacter(int _CharacterIndex)
{
	int CharacterIndex = _CharacterIndex;
	PlayerRender = CreateRender("EnterRoundLevel_Characters.bmp", EnterRoundRenderOrder::Player);
	PlayerRender->CreateAnimation
	({
		.AnimationName = "Player",
		.ImageName = "EnterRoundLevel_Characters.bmp",
		.Start = (CharacterIndex * 4)+ 1,
		.End = (CharacterIndex * 4) + 3,
		.InterTimer = 0.15f
	});

	PlayerRender->SetScale({ 200.f, 200.f });
	PlayerRender->ChangeAnimation("Player");
}

//캐릭터와 투명 거품이 원으로 이동
void EnterRoundCharater::Update(float _DeltaTime)
{
	//라디안각도 증가
	Radian += AddRadian * _DeltaTime;

	//중심 위치는 고정되어 있고 Radian에 따라 위치가 변경된다
	float4 Offset;
	Offset.x = static_cast<float>(cos(Radian * GameEngineMath::PIE) * Radius);
	Offset.y = static_cast<float>(-sin(Radian * GameEngineMath::PIE) * Radius);

	//플레이어와 투명 거품 이동
	PlayerRender->SetPosition(GetPos() + Offset);
	BubbleRender->SetPosition(PlayerRender->GetPosition() + float4::Up * 50.f);
}
