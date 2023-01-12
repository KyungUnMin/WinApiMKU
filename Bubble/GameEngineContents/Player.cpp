#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());
}

void Player::Update() 
{
	SetMove(float4::Left * 1.0f);
}

void Player::Render()
{
	float4 PlayerPos = GetPos();

	//GameEnginePath Path;

	//std::string PathText = Path.GetPathToString();

	// TextOutA(GameEngineWindow::GetDrawHdc(), 0, 0, PathText.c_str(), PathText.size());

	//char Color[4] = {255, 0, 0, 0};
	//int* Ptr = reinterpret_cast<int*>(Color);

	//SetPixel(
	//	GameEngineWindow::GetWindowBackBufferHdc(),
	//	10, 10, *Ptr
	//);

	//Rectangle(
	//	GameEngineWindow::GetDoubleBufferImage()->GetImageDC(),
	//	PlayerPos.ix() - 50, 
	//	PlayerPos.iy() - 50, 
	//	PlayerPos.ix() + 50,
	//	PlayerPos.iy() + 50
	//	);

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("aaaaa.bmp");

	// 특정한 hdc를 다른 hdc에 복사하는 함수
	// bitblt는 이미지를 크기를 줄이거나 늘리는 기능이 없다.

	// GameEngineWindow::GetDoubleBufferImage()->BitCopy(Image, PlayerPos - float4{50, 50}, { 100, 100 });

	// 비율이 어긋날수록 더 느려진다.
	// GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, PlayerPos, { 100, 200 }, { 0, 32 }, {16, 32});

	// 프레임 애니메이션이라고 합니다.
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 4, PlayerPos, { 100, 200 });
}