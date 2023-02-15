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
}


//StringValue�� Text.bmp�� ��Ī���� ������
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