#include "TextLine.h"
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>

std::vector<TextLine*> TextLine::Texts;

//return TextLine::Texts[_Index]
TextLine* TextLine::GetText(int _Index)
{
	if (TextLine::Texts.size() <= _Index)
	{
		MsgAssert("Texts�� �ε��� ������ �Ѿ �����Ͽ����ϴ�");
		return nullptr;
	}

	return Texts[_Index];
}

TextLine::TextLine()
{

}

TextLine::~TextLine()
{
}


void TextLine::Start()
{
	//��� TextLine�߿��� �ѹ��� ����
	static bool IsInit = false;
	if (false == IsInit)
	{
		IsInit = true;

		//�̹��� �ε�
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Image");
		Dir.Move("Common");
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Text.bmp"));
	}

	//�̹��� �ҷ�����
	Image = GameEngineResources::GetInst().ImageFind("Text.bmp");

	//�̹��� �ڸ���
	if (false == Image->IsImageCutting())
	{
		Image->Cut({ 2, 14 }, { 571,114 }, 63, 10);
	}
	
	//�ܺο��� ������ �� �ְ� static �ڷᱸ���� ���
	Texts.push_back(this);
}


//StringValue�� Text.bmp�� ��Ī���� ������
void TextLine::Render(float _DeltaTime)
{
	//�۾� ũ���� ���ݸ�ŭ ������ ���� ��ġ �̵�
	float4 StartPos = GetPos();
	StartPos.y -= static_cast<float>(Scale.hiy());
	StartPos.x -= static_cast<float>(Scale.hix() * StringValue.size());

	//' �Ǵ� " �� ������ ��Ī��Ű�� ���� bool��
	bool isVisited[2] = { false, false };

	for (size_t i = 0; i < StringValue.size(); ++i)
	{
		int idx = 0;

		//! ~ 'Z' ������ �ƽ�Ű�ڵ� ������ ó��
		if ('!' <= StringValue[i] && StringValue[i] <= 'Z')
		{
			//' �� " �� �ƴ� ��쿣 �ƽ�Ű�ڵ� �״�� ó��
			if (StringValue[i] != '\'' && StringValue[i] != '\"')
				idx = static_cast<int>(StringValue[i] - '!');

			//"�� ��쿣 �̹� ��� �ƴ��� Ȯ���ϰ� ó��
			else if (StringValue[i] == '\"')
			{
				idx = isVisited[0] ? 61 : 1;
				isVisited[0] = true;
			}

			//'�� ��쿣 �̹� ��� �ƴ��� Ȯ���ϰ� ó��
			else if (StringValue[i] == '\'')
			{
				idx = isVisited[1] ? 6 : 62;
				isVisited[1] = true;
			}
		}

		//[ �� ] ó�� (Text.bmp���� �� ���ڸ� �ƽ�Ű�ڵ� ������ �ٸ�)
		else if (StringValue[i] == '[')
			idx = 58;
		else if (StringValue[i] == ']')
			idx = 59;

		//�ҹ��� ���ĺ� �ƽ�Ű �ڵ�� ó��
		else if ('a' <= StringValue[i] && StringValue[i] <= 'z')
			idx = static_cast<int>(StringValue[i] - 'a' + 32);

		//�� �� ����(space, \n)���� ���� ó��
		else
			continue;

		//���� ����
		idx += static_cast<int>(Color);

		//��������̹����� TransperBlt
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, idx, StartPos + float4::Right * static_cast<float>(Scale.ix() * i), Scale);
	}
}