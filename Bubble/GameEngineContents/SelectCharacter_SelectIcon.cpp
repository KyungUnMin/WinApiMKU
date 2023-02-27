#include "SelectCharacter_SelectIcon.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineSound.h>
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
	LoadSFX();

	//�̹��� ����
	Render = CreateRender("SelectCharacte_SelectIcon.bmp", SelectCharacterRenderOrder::BackGround);
	Render->SetScale({ 60.f, 40.f });
	Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);

	//Ű  ����
	GameEngineInput::CreateKey("SelectCharacter_Right", KEY_RIGHT);
	GameEngineInput::CreateKey("SelectCharacter_Left", KEY_LEFT);
	GameEngineInput::CreateKey("SelectCharacter_SelectA", KEY_JUMP);
	GameEngineInput::CreateKey("SelectCharacter_SelectB", KEY_ATTACK);
}

void SelectCharacter_SelectIcon::Update(float _DeltaTime)
{
	//ĳ���Ͱ� �̹� ���õƴٸ� CurIndex�� ���� ������ �ʴ´�

	//������ Ű�� �������� && ���� ĳ���Ͱ� ���õ��� �ʾ�����
	if (GameEngineInput::IsDown("SelectCharacter_Right") && false == SelectCharacterLevel::Selected)
	{
		CurIndex = (CurIndex + 1) % 4;
		Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);
		GameEngineResources::GetInst().SoundPlay("MoveCursor.wav");
		return;
	}

	//���� Ű�� �������� && ���� ĳ���Ͱ� ���õ��� �ʾ�����
	else if (GameEngineInput::IsDown("SelectCharacter_Left") && false == SelectCharacterLevel::Selected)
	{
		CurIndex = (CurIndex - 1) < 0 ? 3 : CurIndex - 1;
		Render->SetPosition(SelectCharacterLevel::CharPos[CurIndex] + float4::Up * UpOffset);
		GameEngineResources::GetInst().SoundPlay("MoveCursor.wav");
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
		GameEngineResources::GetInst().SoundPlay("SelectCursor.wav");
	}

}

void SelectCharacter_SelectIcon::LoadSFX()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SFX");
	Dir.Move("Title");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("MoveCursor.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("SelectCursor.wav"));
	IsLoad = true;
}
