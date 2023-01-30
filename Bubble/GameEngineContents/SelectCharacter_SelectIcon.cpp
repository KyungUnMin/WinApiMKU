#include "SelectCharacter_SelectIcon.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsDefine.h"
#include "SelectCharacterLevel.h"

//ȭ���� �߽����κ��� offset
const float SelectCharacter_SelectIcon::UpOffset = 160.f;

SelectCharacter_SelectIcon::SelectCharacter_SelectIcon()
{

}

SelectCharacter_SelectIcon::~SelectCharacter_SelectIcon()
{

}

void SelectCharacter_SelectIcon::Start()
{
	//�̹��� ����
	Render = CreateRender("SelectCharacte_SelectIcon.bmp", SelectCharacterRenderOrder::BackGround);
	Render->SetScale({ 60.f, 40.f });
	Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);

	//Ű  ����
	GameEngineInput::CreateKey("SelectCharacter_Right", RightKey);
	GameEngineInput::CreateKey("SelectCharacter_Left", LeftKey);
	GameEngineInput::CreateKey("SelectCharacter_SelectA", JumpKey);
	GameEngineInput::CreateKey("SelectCharacter_SelectB", AttackKey);
}

void SelectCharacter_SelectIcon::Update(float _DeltaTime)
{
	//ĳ���Ͱ� �̹� ���õƴٸ� CurIndex�� ���� ������ �ʴ´�

	//������ Ű�� �������� && ���� ĳ���Ͱ� ���õ��� �ʾ�����
	if (GameEngineInput::IsDown("SelectCharacter_Right") && false == SelectCharacterLevel::Selected)
	{
		CurIndex = (CurIndex + 1) % 4;
		Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);
		return;
	}

	//���� Ű�� �������� && ���� ĳ���Ͱ� ���õ��� �ʾ�����
	else if (GameEngineInput::IsDown("SelectCharacter_Left") && false == SelectCharacterLevel::Selected)
	{
		CurIndex = (CurIndex - 1) < 0 ? 3 : CurIndex - 1;
		Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);
		return;
	}


	//ĳ���͸� ����������
	if (
		(GameEngineInput::IsDown("SelectCharacter_SelectA") ||
		GameEngineInput::IsDown("SelectCharacter_SelectB")) 
		&&(false == SelectCharacterLevel::Selected)
		)
	{
		SelectCharacterLevel::Selected = true;
	}

}
