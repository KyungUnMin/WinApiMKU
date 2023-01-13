#include "GameEngineRender.h"
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRender::GameEngineRender()
{

}

GameEngineRender::~GameEngineRender()
{

}


//GameEngineResources���� �̹��� ã�ƿ���
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}



//������ �Ǵ� ���� ���� �� Level�� Renders�� ���(Actor������ ȣ��)
void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;

	//GameEngineLevel�� Renders�� ���
	Owner->GetLevel()->PushRender(this);
}


//Level�� Render�� ���� ���� �������Ǵ� �Լ�
void GameEngineRender::Render(float _DeltaTime)
{
	//�������� ����� ������ �� ��ġ
	float4 RenderPos = Owner->GetPos() + Position;

	//�̹����� �ڸ� ���
	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale);
	}

	//�̹����� �ڸ��� ���� ��쿣 ���ҽ� ��üũ�⸦ ���
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, Scale, {0.f, 0.f}, Image->GetImageScale());
	}
}
