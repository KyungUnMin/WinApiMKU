#include "TextLine.h"
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>

std::vector<TextLine*> TextLine::Texts;

TextLine* TextLine::GetText(int _Index)
{
	if (TextLine::Texts.size() <= _Index)
	{
		MsgAssert("Texts의 인덱스 범위를 넘어서 접근하였습니다");
		return nullptr;
	}

	return Texts[_Index];
}

TextLine::TextLine()
{

}

TextLine::~TextLine()
{
	StringValue.clear();
}


void TextLine::Start()
{
	static bool IsInit = false;
	if (false == IsInit)
	{
		IsInit = true;
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Common");
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Text.bmp"));
	}

	Image = GameEngineResources::GetInst().ImageFind("Text.bmp");
	Image->Cut({ 2, 14 }, { 571,114 }, 63, 10);
	Texts.push_back(this);
}


void TextLine::Render(float _DeltaTime)
{
	float4 StartPos = GetPos();
	StartPos.y -= static_cast<float>(Scale.hiy());
	StartPos.x -= static_cast<float>(Scale.hix() * StringValue.size());

	bool isVisited[2] = { false, false };
	for (size_t i = 0; i < StringValue.size(); ++i)
	{
		int idx = 0;

		if ('!' <= StringValue[i] && StringValue[i] <= 'Z')
		{
			if (StringValue[i] != '\'' && StringValue[i] != '\"')
				idx = static_cast<int>(StringValue[i] - '!');
			else if (StringValue[i] == '\"')
			{
				idx = isVisited[0] ? 61 : 1;
				isVisited[0] = true;
			}
			else if (StringValue[i] == '\'')
			{
				idx = isVisited[1] ? 6 : 62;
				isVisited[1] = true;
			}
		}
		else if (StringValue[i] == '[')
			idx = 58;
		else if (StringValue[i] == ']')
			idx = 59;
		else if ('a' <= StringValue[i] && StringValue[i] <= 'z')
			idx = static_cast<int>(StringValue[i] - 'a' + 32);
		else
			continue;

		idx += static_cast<int>(Color);

		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, idx, StartPos + float4::Right * static_cast<float>(Scale.ix() * i), Scale);
	}
}


/*GameEngineRender* Render = CreateRender("Text.bmp", RenderOrder::UI);
	GameEngineImage* Image = Render->GetImage();
	Image->Cut({ 2, 14 }, { 571,114 }, 63, 10);
	Render->SetFrame(FrameCnt);
	Render->SetScale({ 100.f, 100.f });
	Render->SetPosition({ 100.f, 100.f });*/