#pragma once

class C_FontManager
{
public:

	void DrawWord(Math::Vector2 a_pos, std::string a_word, float a_scale, Math::Color a_color);
	void DrawNumber(Math::Vector2 a_pos, int a_number, int a_minDigit, float a_scale, Math::Color a_color);

private:

	const Math::Vector2 BASETEXTSIZE = { 18.0f,28.0f };

	static const int TEXTNUM_ONELINE = 13;
	static const int TEXTNUM = 63;
	const char TEXTID[TEXTNUM] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	
	C_FontManager(){ Init(); }
	~C_FontManager(){ Release(); }

	void Init();
	void Release();

	Math::Rectangle FindTextRec(char a_word);

	KdTexture m_fontTex;

public:

	static C_FontManager& GetInstance()
	{
		static C_FontManager instance;
		return instance;
	}

};

#define FONTMGR C_FontManager::GetInstance()