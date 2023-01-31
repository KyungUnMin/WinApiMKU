#include "SelectCharacterBackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "SelectCharacterLevel.h"

const float4 SelectCharacterBackGround::Offset[4] =
{
	{-1.f, -1.f},
	{1.f, -1.f},
	{-1.f, 1.f},
	{1.f, 1.f}
};

const float	SelectCharacterBackGround::MoveSpeed = 100.f;

SelectCharacterBackGround::SelectCharacterBackGround()
{

}

SelectCharacterBackGround::~SelectCharacterBackGround()
{

}

void SelectCharacterBackGround::Start()
{
	ScreenSize = GameEngineWindow::GetScreenSize();
	SetPos(ScreenSize);

	//�� 4���� �������� ����
	//�� actor�� �������� 1234�и�ó�� ����
	for (size_t i = 0; i < 4; ++i)
	{
		GameEngineRender* Render = CreateRender("SelectCharacter_CheckPattern.bmp", SelectCharacterRenderOrder::BackGround);
		Render->SetScale(ScreenSize);
		Render->SetPosition(ScreenSize.half() * Offset[i]);
	}
}

void SelectCharacterBackGround::Update(float _DeltaTime)
{
	//vector(-�ػ�.x, -�ػ�.y) �������� �̵�
	float4 Dir = ScreenSize.half() * Offset[0];
	Dir.Normalize();
	SetMove(Dir * MoveSpeed * _DeltaTime);

	//�� Actor�� ��ġ�� (0,0)���� �۴ٸ� ��ũ�� ũ�⸸ŭ �̵�
	if (GetPos() < float4::Zero)
	{
		SetMove(ScreenSize);
	}
}
