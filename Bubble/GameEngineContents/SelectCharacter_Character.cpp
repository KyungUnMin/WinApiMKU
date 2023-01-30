#include "SelectCharacter_Character.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "SelectCharacterLevel.h"

SelectCharacter_Character::SelectCharacter_Character()
{

}

SelectCharacter_Character::~SelectCharacter_Character()
{

}


void SelectCharacter_Character::Start()
{
	//캐릭터가 들고 있는 나무막대기
	NoticeRender = CreateRender("SelectCharacter_NoticeHandle.bmp", SelectCharacterRenderOrder::NoticeHandle);
	NoticeRender->SetScale({ 100.f, 100.f });
	NoticeRender->SetPosition({ 30.f, -80.f });

	//캐릭터 이름
	NameRender = CreateRender("SelectCharacter_CharacterName.bmp", SelectCharacterRenderOrder::UI);
	NameRender->SetScale({ 80.f, 40.f });
	NameRender->SetPosition({ 30.f, -105.f });

	//캐릭터모음 이미지
	CharRender = CreateRender("SelectCharacter_Characters.bmp", SelectCharacterRenderOrder::Character);
	CharRender->SetScale({ 200.f, 200.f });

	//캐릭터가 선택되었을 때 투명 거품 애니메이션
	ClearBubble = CreateRender("SelectCharacter_ClearBubble.bmp", SelectCharacterRenderOrder::Bubble);
	ClearBubble->CreateAnimation
	({
		.AnimationName = "ClearBubble",
		.ImageName = "SelectCharacter_ClearBubble.bmp",
		.Start = 0,
		.End = 2,
		.InterTimer = 0.15f
	});
	
	ClearBubble->ChangeAnimation("ClearBubble");
	ClearBubble->SetScale({1.f, 1.f});
	ClearBubble->SetPosition({ 0.f, -25.f });

	//현재는 캐릭터가 선택되지 않았기때문에 Off
	ClearBubble->Off();
}

void SelectCharacter_Character::Update(float _DeltaTime)
{
	//이 캐릭터가 선택되었다면 ClearBubble이 On 된다
	if (false == ClearBubble->IsUpdate())
		return;

	//Bubble의 크기가 1에서 200까지 1초당 300의 속도로 커짐
	float4 Scale = ClearBubble->GetScale();
	Scale += float4{ 1.f, 1.f } *BubbleGrowValue * _DeltaTime;
	if (Scale < float4{ 1.f, 1.f } *MaxBubbleScale)
	{
		ClearBubble->SetScale(Scale);
	}
}


//해당 캐릭터 타입 캐릭터 애니메이션 생성(외부에서 호출해야 함)
void SelectCharacter_Character::SetCharacterType(PlayerCharacterType _Type)
{
	int CharIndex = static_cast<int>(_Type);

	NameRender->SetFrame(CharIndex);

	//Idle 애니메이션 생성
	CharRender->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "SelectCharacter_Characters.bmp",
		.Start = (CharIndex * 4),
		.End = (CharIndex * 4),
		.InterTimer = FLT_MAX
	});

	//Selected 애니메이션 생성
	CharRender->CreateAnimation
	({
		.AnimationName = "Selected",
		.ImageName = "SelectCharacter_Characters.bmp",
		.Start = (CharIndex * 4) + 1,
		.End = (CharIndex * 4) + 3,
		.InterTimer = 0.15f
	});

	//처음엔 Idle 애니메이션으로 동작
	CharRender->ChangeAnimation("Idle");
}

//캐릭터 선택되었을때 애니메이션 전환
void SelectCharacter_Character::Select()
{
	CharRender->ChangeAnimation("Selected");

	//캐릭터가 들고있던 나무막대기 Off
	NoticeRender->Off();
	//캐릭터의 이름 off
	NameRender->Off();
	//캐릭터 뒤쪽 투명 버블 on
	ClearBubble->On();
}

void SelectCharacter_Character::Reset()
{
	CharRender->ChangeAnimation("Idle");
	NoticeRender->On();
	NameRender->On();
	ClearBubble->Off();
	ClearBubble->SetScale({ 1.f, 1.f });
}
