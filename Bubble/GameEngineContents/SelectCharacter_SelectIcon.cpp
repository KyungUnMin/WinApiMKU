#include "SelectCharacter_SelectIcon.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "SelectCharacterLevel.h"

//화면의 중심으로부터 offset
const float SelectCharacter_SelectIcon::UpOffset = 160.f;

SelectCharacter_SelectIcon::SelectCharacter_SelectIcon()
{

}

SelectCharacter_SelectIcon::~SelectCharacter_SelectIcon()
{

}

void SelectCharacter_SelectIcon::Start()
{
	//이미지 생성
	Render = CreateRender("SelectCharacte_SelectIcon.bmp", SelectCharacterRenderOrder::BackGround);
	Render->SetScale({ 60.f, 40.f });
	Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);

	//키  생성
	GameEngineInput::CreateKey("SelectCharacter_Right", RightKey);
	GameEngineInput::CreateKey("SelectCharacter_Left", LeftKey);
	GameEngineInput::CreateKey("SelectCharacter_SelectA", JumpKey);
	GameEngineInput::CreateKey("SelectCharacter_SelectB", AttackKey);
}

void SelectCharacter_SelectIcon::Update(float _DeltaTime)
{
	//캐릭터가 이미 선택됐다면 CurIndex의 값은 변하지 않는다

	//오른쪽 키를 눌렀을때 && 아직 캐릭터가 선택되지 않았을때
	if (GameEngineInput::IsDown("SelectCharacter_Right") && false == SelectCharacterLevel::Selected)
	{
		CurIndex = (CurIndex + 1) % 4;
		Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);
		return;
	}

	//왼쪽 키를 눌렀을때 && 아직 캐릭터가 선택되지 않았을때
	else if (GameEngineInput::IsDown("SelectCharacter_Left") && false == SelectCharacterLevel::Selected)
	{
		CurIndex = (CurIndex - 1) < 0 ? 3 : CurIndex - 1;
		Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);
		return;
	}


	//캐릭터를 선택했을때
	if (
		(GameEngineInput::IsDown("SelectCharacter_SelectA") ||
		GameEngineInput::IsDown("SelectCharacter_SelectB")) 
		&&(false == SelectCharacterLevel::Selected)
		)
	{
		SelectCharacterLevel::Selected = true;
	}

}
