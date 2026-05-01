#include "Number.h"

void C_Number::DrawNumber(Math::Vector2 a_pos, int a_number, int a_minDigit, float a_scale)
{
	//一応リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	const Math::Vector2 NumberSize = BASENUMBERSIZE * a_scale;
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

	float LeftPosX = a_pos.x - (NumberSize.x / 2.0f  * (digits.size() - 1));

	//桁数回繰り返し（a_posが真ん中になるように）
	for (int i = 0;i < digits.size();i++)
	{
		int number = *(digits.rbegin() + i);

		Math::Rectangle rec = { (long)(number * BASENUMBERSIZE.x),0,(long)BASENUMBERSIZE.x,(long)BASENUMBERSIZE.y };

		SHADER.m_spriteShader.DrawTex(&m_numberTex, LeftPosX + NumberSize.x * i, a_pos.y, NumberSize.x, NumberSize.y, &rec);
	}
}

void C_Number::Init()
{
	m_numberTex.Load("Texture/Fonts/Number.png");
}

void C_Number::Release()
{
	m_numberTex.Release();
}
