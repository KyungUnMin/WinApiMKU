#include "GameEngineRender.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineCore.h"

GameEngineRender::GameEngineRender()
{

}

GameEngineRender::~GameEngineRender()
{

}


void GameEngineRender::SetRotFilter(const std::string_view& _ImageName)
{
	RotationFilter = GameEngineResources::GetInst().ImageFind(_ImageName);
}


//GameEngineResources���� �̹��� ã�ƿ���
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
	//SetScaleToImage();
}

void GameEngineRender::SetImageToScaleToImage(const std::string_view& _ImageName)
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
	//(Render��ü�� Level�� Actor�� �ڷᱸ��, �� ������ �����Ѵ�)
	// ���� �� �Ҹ��� Actor, Update�� Level
	//GameEngineLevel�� Renders�� ���
	GetActor()->GetLevel()->PushRender(this, _Order);
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
		CurrentTime += FrameTime[CurrentIndex];
	}

}


//�� �Լ��� ���� ���� �����ϸ� TextRender��尡 �ȴ�
void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor, const float4& _TextBoxScale)
{
	RenderText	= _Text;
	TextHeight = _TextHeight;
	TextType = _TextType;
	Align = _TextAlign;
	TextColor = _TextColor;
	TextBoxScale = _TextBoxScale;
}


//Level�� Render�� ���� ���� �������Ǵ� �Լ�
void GameEngineRender::Render(float _DeltaTime)
{
	if (RenderText != "")
	{
		TextRender(_DeltaTime);
	}
	else
	{
		ImageRender(_DeltaTime);
	}
}


void GameEngineRender::TextRender(float _DeltaTime)
{
	//ī�޶� ���
	float4 CameraPos = float4::Zero;
	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	//������ ��ġ ����ؼ� �ؽ�Ʈ ���
	float4 RenderPos = GetActorPlusPos() - CameraPos;



	HDC hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	HFONT hFont, OldFont;
	LOGFONTA lf;
	lf.lfHeight = TextHeight;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = HANGEUL_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	lstrcpy(lf.lfFaceName, TEXT(TextType.c_str()));
	hFont = CreateFontIndirect(&lf);
	OldFont = static_cast<HFONT>(SelectObject(hdc, hFont));

	//SetTextAlign(hdc, static_cast<UINT>(Align));
	SetTextColor(hdc, TextColor);
	SetBkMode(hdc, TRANSPARENT);

	RECT Rect;
	Rect.left = RenderPos.ix();
	Rect.top = RenderPos.iy();
	Rect.right = RenderPos.ix() + TextBoxScale.ix();
	Rect.bottom = RenderPos.iy() + TextBoxScale.iy();

	if (true == GameEngineCore::GetInst()->IsDebug())
	{
		HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
		HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(DoubleDC, myBrush));
		HPEN myPen = CreatePen(PS_DASH, 0, RGB(0, 0, 0));
		HPEN oldPen = static_cast<HPEN>(SelectObject(DoubleDC, myPen));
		Rectangle(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), Rect.left, Rect.top, Rect.right, Rect.bottom);

		SelectObject(DoubleDC, oldBrush);
		DeleteObject(myBrush);
		SelectObject(DoubleDC, oldPen);
		DeleteObject(myPen);
	}

	DrawTextA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderText.c_str(), static_cast<int>(RenderText.size()), &Rect, DT_LEFT);

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);
}

void GameEngineRender::ImageRender(float _DeltaTime)
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

		RotationFilter = CurrentAnimation->FilterImage;
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
		if (0.0f != Angle)
		{
			if (nullptr == RotationFilter)
			{
				MsgAssert("ȸ����ų�� ���� �̹��� �Դϴ�. ���Ͱ� �������� �ʽ��ϴ�.");
				return;
			}

			GameEngineWindow::GetDoubleBufferImage()->PlgCopy(Image, Frame, RenderPos, GetScale(), Angle, RotationFilter);
		}
		else if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), TransColor);
		}
		else if(Alpha < 255)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, Frame, RenderPos, GetScale(), Alpha);
		}
	}

	//�̹����� �ڸ��� ���� ��쿣 ���ҽ� ��üũ�⸦ ���
	else
	{
		if (0.0f != Angle)
		{
			if (nullptr == RotationFilter)
			{
				MsgAssert("ȸ����ų�� ���� �̹��� �Դϴ�. ���Ͱ� �������� �ʽ��ϴ�.");
			}

			GameEngineWindow::GetDoubleBufferImage()->PlgCopy(Image, Frame, RenderPos, GetScale(), Angle, RotationFilter);
		}
		else if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), TransColor);
		}
		else if (Alpha < 255)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), Alpha);
		}
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

	//ȸ���ϴ� �̹����� ���
	if ("" != _Parameter.FilterName)
	{
		NewAnimation.FilterImage = GameEngineResources::GetInst().ImageFind(_Parameter.FilterName);

		if (nullptr == NewAnimation.FilterImage)
		{
			MsgAssert("�������� �ʴ� �̹����� �����̼� ���͸� ����Ҽ� �����ϴ�.");
		}
	}


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