#include "FontManager.h"

void C_FontManager::DrawWord(Math::Vector2 a_pos, E_TextDrawPos a_drawPos, std::string a_word, float a_scale, Math::Color a_color)
{
	//一応リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	//文字サイズ
	const Math::Vector2 TextSize = BASETEXTSIZE * a_scale;

	//左端の位置決定
	float LeftPosX = 0.0f;
	switch (a_drawPos)
	{
	case E_TextDrawPos::Left:
		LeftPosX = a_pos.x + TextSize.x / 2.0f;
		break;
	case E_TextDrawPos::Center:
		LeftPosX = a_pos.x - (TextSize.x / 2.0f * (a_word.size() - 1));
		break;
	case E_TextDrawPos::Right:
		LeftPosX = a_pos.x - (TextSize.x * (a_word.size() - 1)) - TextSize.x / 2.0f;
		break;
	}

	for (int i = 0;i < a_word.size();i++)
	{
		char ch = *(a_word.begin() + i);
		Math::Rectangle rec = FindTextRec(ch);

		SHADER.m_spriteShader.DrawTex(&m_fontTex, LeftPosX + TextSize.x * i, a_pos.y, TextSize.x, TextSize.y, &rec, &a_color);
	}
}

void C_FontManager::DrawNumber(Math::Vector2 a_pos, E_TextDrawPos a_drawPos, int a_number, int a_minDigit, float a_scale, Math::Color a_color)
{
	//一応リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	//文字サイズ
	const Math::Vector2 NumberSize = BASETEXTSIZE * a_scale;
	
	//分解準備
	int baseNum = a_number;
	std::vector<int> digits;
	
	//桁分解
	while (baseNum >= 10)
	{
		digits.push_back(baseNum % 10);
		baseNum /= 10;
	}
	digits.push_back(baseNum);

	while (digits.size() < a_minDigit)
	{
		digits.push_back(0);
	}

	//左端の位置決定
	float LeftPosX = 0.0f;
	switch (a_drawPos)
	{
	case E_TextDrawPos::Left:
		LeftPosX = a_pos.x + NumberSize.x / 2.0f;
		break;
	case E_TextDrawPos::Center:
		LeftPosX = a_pos.x - (NumberSize.x / 2.0f * (digits.size() - 1));
		break;
	case E_TextDrawPos::Right:
		LeftPosX = a_pos.x - (NumberSize.x * (digits.size() - 1)) - NumberSize.x / 2.0f;
		break;
	}

	//桁数回繰り返し（a_posが真ん中になるように）
	for (int i = 0;i < digits.size();i++)
	{
		int number = *(digits.rbegin() + i);

		Math::Rectangle rec = FindTextRec('0' + number);

		SHADER.m_spriteShader.DrawTex(&m_fontTex, LeftPosX + NumberSize.x * i, a_pos.y, NumberSize.x, NumberSize.y, &rec, &a_color);
	}
}

std::string C_FontManager::ConvertToTime(int a_min, int a_sec, int a_frame)
{
	int micS = (int)(a_frame / 60.0f * 100.0f);

	std::string ans = "";
	ans += ('0' + a_min / 10);
	ans += ('0' + a_min % 10);
	ans += ":";
	ans += ('0' + a_sec / 10);
	ans += ('0' + a_sec % 10);
	ans += ".";
	ans += ('0' + micS / 10);
	ans += ('0' + micS % 10);

	return(ans);
}

void C_FontManager::Init()
{
	m_fontTex.Load("Texture/Fonts/Fonts.png");	
}

void C_FontManager::Release()
{
	m_fontTex.Release();
}

Math::Rectangle C_FontManager::FindTextRec(char a_word)
{
	for (int i = 0;i < TEXTNUM;i++)
	{
		if (TEXTID[i] == a_word)
		{
			Math::Rectangle rec = { (long)((i % TEXTNUM_ONELINE) * BASETEXTSIZE.x),(long)((i / TEXTNUM_ONELINE) * BASETEXTSIZE.y),(long)BASETEXTSIZE.x,(long)BASETEXTSIZE.y };
			return(rec);
		}
	}
	return(Math::Rectangle{ 0,0,0,0 });
}
