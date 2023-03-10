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


//GameEngineResources에서 이미지 찾아오기
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


//렌더링 이미지를 실제 리소스의 이미지 크기로 설정
void GameEngineRender::SetScaleToImage()
{
	if (nullptr == Image)
	{
		MsgAssert("이미지를 세팅하지 않았는데 이미지 크기를 변경하려고 했습니다");
		return;
	}

	SetScale(Image->GetImageScale());
}


//렌더링 되는 순서 결정 및 Level의 Renders에 등록(Actor에서만 호출)
void GameEngineRender::SetOrder(int _Order)
{
	//(Render객체를 Level와 Actor의 자료구조, 두 곳에서 관리한다)
	// 생성 및 소멸은 Actor, Update는 Level
	//GameEngineLevel의 Renders에 등록
	GetActor()->GetLevel()->PushRender(this, _Order);
}


void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("이미지가 존재하지 않는 랜더러에 프레임을 지정하려고 했습니다.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("유요하지 않은 이미지인덱스 입니다.");
	}

	Frame = _Frame;
}



bool GameEngineRender::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
	return CurrentIndex == Value;
}

//CurrentTime동안 FrameIndex[CurrentIndex]을 바탕으로 렌더링할 인덱스 결정
void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime -= _DeltaTime;

	//다음 프레임으로 넘어가야 하는 시간일때
	if (CurrentTime <= 0.0f)
	{
		++CurrentIndex;

		//애니메이션의 모든 프레임을 다 출력했을때
		if (FrameIndex.size() <= CurrentIndex)
		{
			//반복재생이라면 첫 프레임으로 이동
			if (true == Loop)
			{
				CurrentIndex = 0;
			}
			//반복재생이 아니라면 마지막 프레임 유지
			else
			{
				CurrentIndex = static_cast<int>(FrameIndex.size() - 1);
			}
		}

		//시간 재설정
		CurrentTime += FrameTime[CurrentIndex];
	}

}


//이 함수를 통해 값을 설정하면 TextRender모드가 된다
void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor, const float4& _TextBoxScale)
{
	RenderText	= _Text;
	TextHeight = _TextHeight;
	TextType = _TextType;
	Align = _TextAlign;
	TextColor = _TextColor;
	TextBoxScale = _TextBoxScale;
}


//Level의 Render를 통해 실제 렌더링되는 함수
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
	//카메라 계산
	float4 CameraPos = float4::Zero;
	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	//렌더링 위치 계산해서 텍스트 출력
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
	//애니메이션 모드라면
	if (nullptr != CurrentAnimation)
	{
		//그려야 할 인덱스 계산
		CurrentAnimation->Render(_DeltaTime);

		//그려야 할 인덱스 설정
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];

		//이미지 설정
		//(CreateAnimation으로 애니메이션을 생성했다면
		//GameEngineRender::Image는 별도로 지정해주지 않았다)
		Image = CurrentAnimation->Image;

		RotationFilter = CurrentAnimation->FilterImage;
	}

	if (nullptr == Image)
	{
		MsgAssert("이미지를 세팅해주지 않았습니다");
		return;
	}

	//카메라에 따른 렌더링 위치 변경
	float4 CameraPos = float4::Zero;
	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	//오프셋이 적용된 렌더링 될 위치
	float4 RenderPos = GetActorPlusPos() - CameraPos;

	//이미지를 자른 경우
	if (true == Image->IsImageCutting())
	{
		if (0.0f != Angle)
		{
			if (nullptr == RotationFilter)
			{
				MsgAssert("회전시킬수 없는 이미지 입니다. 필터가 존재하지 않습니다.");
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

	//이미지를 자르지 않은 경우엔 리소스 전체크기를 출력
	else
	{
		if (0.0f != Angle)
		{
			if (nullptr == RotationFilter)
			{
				MsgAssert("회전시킬수 없는 이미지 입니다. 필터가 존재하지 않습니다.");
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
	//이미지 불러오기
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Parameter.ImageName);
	if (nullptr == Image)
	{
		MsgAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다 : ");
		return;
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다");
		return;
	}

	std::string UpperName = GameEngineString::ToUpper(_Parameter.AnimationName);
	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션입니다");
		return;
	}

	//map에서 애니메이션을 생성하고 받아옴
	FrameAnimation& NewAnimation = Animation[UpperName];
	NewAnimation.Image = Image;

	//회전하는 이미지의 경우
	if ("" != _Parameter.FilterName)
	{
		NewAnimation.FilterImage = GameEngineResources::GetInst().ImageFind(_Parameter.FilterName);

		if (nullptr == NewAnimation.FilterImage)
		{
			MsgAssert("존재하지 않는 이미지로 로테이션 필터를 사용할수 없습니다.");
		}
	}


//[출력할 애니메이션 프레임 인덱스  순서 저장]

	//애니메이션 프레임이 순차적이지 않은 경우
	if (0 != _Parameter.FrameIndex.size())
	{
		//바로 해당 인덱스의 값을 물려받는다
		NewAnimation.FrameIndex = _Parameter.FrameIndex;
	}

	//애니메이션 프레임이 순차적인 경우 
	else
	{
		//Start부터 End까지의 프레임인덱스 저장
		for (int i = _Parameter.Start; i <= _Parameter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

//[각 애니메이션 프레임의 출력 시간 지정]
	
	//애니메이션 프레임마다 출력 시간이 다른 경우
	if (0 != _Parameter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Parameter.FrameTime;
	}

	//애니메이션 프레임마다 출력 시간이 같은 경우
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Parameter.InterTimer);
		}
	}

	//반복재생 여부
	NewAnimation.Loop = _Parameter.Loop;

	//이 애니메이션의 소유 렌더러는 this
	NewAnimation.Parent = this;
}


//애니메이션 변환
void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);
	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다 : " + UpperName);
		return;
	}

	//변경하려는 애니메이션이 현재 애니메이션인 경우 강제로 바꾸지 않는 이상 return
	if (false == _ForceChange && CurrentAnimation == &Animation[UpperName])
		return;

	//애니메이션 변경
	CurrentAnimation = &Animation[UpperName];
	//해당 애니메이션 인덱스 설정
	CurrentAnimation->CurrentIndex = 0;
	//해당 애니메이션 시간 설정
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}