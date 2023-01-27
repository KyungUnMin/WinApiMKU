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
	NoticeRender = CreateRender("SelectCharacter_NoticeHandle.bmp", SelectCharacterRenderOrder::NoticeHandle);
	NoticeRender->SetScale({ 100.f, 100.f });
	NoticeRender->SetPosition({ 30.f, -80.f });

	NameRender = CreateRender("SelectCharacter_CharacterName.bmp", SelectCharacterRenderOrder::UI);
	NameRender->SetScale({ 80.f, 40.f });
	NameRender->SetPosition({ 30.f, -105.f });

	CharRender = CreateRender("SelectCharacter_Characters.bmp", SelectCharacterRenderOrder::Character);
	CharRender->SetScale({ 200.f, 200.f });

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
	ClearBubble->Off();
}

void SelectCharacter_Character::Update(float _DeltaTime)
{
	if (false == ClearBubble->IsUpdate())
		return;

	float4 Scale = ClearBubble->GetScale();
	Scale += float4{ 1.f, 1.f } *BubbleGrowValue * _DeltaTime;
	if (Scale < float4{ 1.f, 1.f } *MaxBubbleScale)
	{
		ClearBubble->SetScale(Scale);
	}
}


void SelectCharacter_Character::SetCharacterType(PlayerCharacterType _Type)
{
	int CharIndex = static_cast<int>(_Type);

	NameRender->SetFrame(CharIndex);

	CharRender->CreateAnimation
	({
		.AnimationName = "Idle",
		.ImageName = "SelectCharacter_Characters.bmp",
		.Start = (CharIndex * 4),
		.End = (CharIndex * 4),
		.InterTimer = FLT_MAX
	});

	CharRender->CreateAnimation
	({
		.AnimationName = "Selected",
		.ImageName = "SelectCharacter_Characters.bmp",
		.Start = (CharIndex * 4) + 1,
		.End = (CharIndex * 4) + 3,
		.InterTimer = 0.15f
	});

	CharRender->ChangeAnimation("Idle");
}

void SelectCharacter_Character::Select()
{
	CharRender->ChangeAnimation("Selected");
	NoticeRender->Off();
	NameRender->Off();
	ClearBubble->On();
}
