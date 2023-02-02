#include "GameEngineRender.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

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
	SetScaleToImage();
}


//������ �̹����� ���� ���ҽ��� �̹��� ũ��� ����
void GameEngineRender::SetScaleToImage()
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʾҴµ� �̹��� ũ�⸦ �����Ϸ��� �߽��ϴ�");
		return;
	}

	SetScale(Image->GetImageScale());
}


//������ �Ǵ� ���� ���� �� Level�� Renders�� ���(Actor������ ȣ��)
void GameEngineRender::SetOrder(int _Order)
{
	GameEngineObject::SetOrder(_Order);

	//(Render��ü�� Level�� Actor�� �ڷᱸ��, �� ������ �����Ѵ�)
	// ���� �� �Ҹ��� Actor, Update�� Level
	//GameEngineLevel�� Renders�� ���
	GetActor()->GetLevel()->PushRender(this);
}


void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʴ� �������� �������� �����Ϸ��� �߽��ϴ�.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("�������� ���� �̹����ε��� �Դϴ�.");
	}

	Frame = _Frame;
}



bool GameEngineRender::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
	return CurrentIndex == Value;
}

//CurrentTime���� FrameIndex[CurrentIndex]�� �������� �������� �ε��� ����
void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime -= _DeltaTime;

	//���� ���������� �Ѿ�� �ϴ� �ð��϶�
	if (CurrentTime <= 0.0f)
	{
		++CurrentIndex;

		//�ִϸ��̼��� ��� �������� �� ���������
		if (FrameIndex.size() <= CurrentIndex)
		{
			//�ݺ�����̶�� ù ���������� �̵�
			if (true == Loop)
			{
				CurrentIndex = 0;
			}
			//�ݺ������ �ƴ϶�� ������ ������ ����
			else
			{
				CurrentIndex = static_cast<int>(FrameIndex.size() - 1);
			}
		}

		//�ð� �缳��
		CurrentTime = FrameTime[CurrentIndex];
	}

}


//Level�� Render�� ���� ���� �������Ǵ� �Լ�
void GameEngineRender::Render(float _DeltaTime)
{
	//�ִϸ��̼� �����
	if (nullptr != CurrentAnimation)
	{
		//�׷��� �� �ε��� ���
		CurrentAnimation->Render(_DeltaTime);

		//�׷��� �� �ε��� ����
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];

		//�̹��� ����
		//(CreateAnimation���� �ִϸ��̼��� �����ߴٸ�
		//GameEngineRender::Image�� ������ ���������� �ʾҴ�)
		Image = CurrentAnimation->Image;
	}

	if (nullptr == Image)
	{
		MsgAssert("�̹����� ���������� �ʾҽ��ϴ�");
		return;
	}

	//ī�޶� ���� ������ ��ġ ����
	float4 CameraPos = float4::Zero;
	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	//�������� ����� ������ �� ��ġ
	float4 RenderPos = GetActorPlusPos() - CameraPos;

	//�̹����� �ڸ� ���
	if (true == Image->IsImageCutting())
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), TransColor);
	}

	//�̹����� �ڸ��� ���� ��쿣 ���ҽ� ��üũ�⸦ ���
	else
	{
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), {0.f, 0.f}, Image->GetImageScale()), TransColor;
	}
}




bool GameEngineRender::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}

void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Parameter)
{
	//�̹��� �ҷ�����
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Parameter.ImageName);
	if (nullptr == Image)
	{
		MsgAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ� : ");
		return;
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�");
		return;
	}

	std::string UpperName = GameEngineString::ToUpper(_Parameter.AnimationName);
	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼��Դϴ�");
		return;
	}

	//map���� �ִϸ��̼��� �����ϰ� �޾ƿ�
	FrameAnimation& NewAnimation = Animation[UpperName];
	NewAnimation.Image = Image;


//[����� �ִϸ��̼� ������ �ε���  ���� ����]

	//�ִϸ��̼� �������� ���������� ���� ���
	if (0 != _Parameter.FrameIndex.size())
	{
		//�ٷ� �ش� �ε����� ���� �����޴´�
		NewAnimation.FrameIndex = _Parameter.FrameIndex;
	}

	//�ִϸ��̼� �������� �������� ��� 
	else
	{
		//Start���� End������ �������ε��� ����
		for (int i = _Parameter.Start; i <= _Parameter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

//[�� �ִϸ��̼� �������� ��� �ð� ����]
	
	//�ִϸ��̼� �����Ӹ��� ��� �ð��� �ٸ� ���
	if (0 != _Parameter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Parameter.FrameTime;
	}

	//�ִϸ��̼� �����Ӹ��� ��� �ð��� ���� ���
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Parameter.InterTimer);
		}
	}

	//�ݺ���� ����
	NewAnimation.Loop = _Parameter.Loop;

	//�� �ִϸ��̼��� ���� �������� this
	NewAnimation.Parent = this;
}


//�ִϸ��̼� ��ȯ
void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);
	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ��� �߽��ϴ� : " + UpperName);
		return;
	}

	//�����Ϸ��� �ִϸ��̼��� ���� �ִϸ��̼��� ��� ������ �ٲ��� �ʴ� �̻� return
	if (false == _ForceChange && CurrentAnimation == &Animation[UpperName])
		return;

	//�ִϸ��̼� ����
	CurrentAnimation = &Animation[UpperName];
	//�ش� �ִϸ��̼� �ε��� ����
	CurrentAnimation->CurrentIndex = 0;
	//�ش� �ִϸ��̼� �ð� ����
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}