#include "TextLine.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>

TextLine::TextLine()
{

}

TextLine::~TextLine()
{
}


void TextLine::Start()
{
	//모든 TextLine중에서 한번만 실행
	static bool IsInit = false;
	if (false == IsInit)
	{
		IsInit = true;

		//이미지 로드
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Common");
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Text.bmp"));
	}

	//이미지 불러오기
	Image = GameEngineResources::GetInst().ImageFind("Text.bmp");

	//이미지 자르기
	if (false == Image->IsImageCutting())
	{
		Image->Cut({ 2, 14 }, { 571,114 }, 63, 10);
	}
}


//StringValue와 Text.bmp를 매칭시켜 렌더링
void TextLine::Render(float _DeltaTime)
{
	if (true == StringValue.empty())
		return;

	float4 StartPos = GetPos();
	StartPos.y -= static_cast<float>(Scale.hiy());

	if (TextAlignType::Center == AlignType)
	{
		StartPos.x -= Scale.hx() * StringValue.size();
	}
	else if (TextAlignType::Right == AlignType)
	{
		StartPos.x -= Scale.x * StringValue.size();
	}

	//' 또는 " 의 방향을 매칭시키기 위한 bool값
	bool isVisited[2] = { false, false };

	for (size_t i = 0; i < StringValue.size(); ++i)
	{
		int idx = 0;

		//! ~ 'Z' 까지의 아스키코드 순으로 처리
		if ('!' <= StringValue[i] && StringValue[i] <= 'Z')
		{
			//' 나 " 가 아닌 경우엔 아스키코드 그대로 처리
			if (StringValue[i] != '\'' && StringValue[i] != '\"')
				idx = static_cast<int>(StringValue[i] - '!');

			//"인 경우엔 이미 출력 됐는지 확인하고 처리
			else if (StringValue[i] == '\"')
			{
				idx = isVisited[0] ? 61 : 1;
				isVisited[0] = true;
			}

			//'인 경우엔 이미 출력 됐는지 확인하고 처리
			else if (StringValue[i] == '\'')
			{
				idx = isVisited[1] ? 6 : 62;
				isVisited[1] = true;
			}
		}

		//[ 와 ] 처리 (Text.bmp에서 이 글자만 아스키코드 순서와 다름)
		else if (StringValue[i] == '[')
			idx = 58;
		else if (StringValue[i] == ']')
			idx = 59;

		//소문자 알파벳 아스키 코드로 처리
		else if ('a' <= StringValue[i] && StringValue[i] <= 'z')
			idx = static_cast<int>(StringValue[i] - 'a' + 32);

		//그 외 글자(space, \n)등은 띄어쓰기 처리
		else
			continue;

		//색상값 결정
		idx += static_cast<int>(Color);

		//더블버퍼이미지에 TransperBlt
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, idx, StartPos + float4::Right * static_cast<float>(Scale.ix() * i), Scale);
	}
}