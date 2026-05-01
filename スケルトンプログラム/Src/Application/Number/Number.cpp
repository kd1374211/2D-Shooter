#include "Number.h"

void C_Number::DrawNumber(Math::Vector2 a_pos, int a_number, float a_scale)
{
	//一応リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

void C_Number::Init()
{
	m_numberTex.Load("Texture/Fonts/Number.png");
}

void C_Number::Release()
{
	m_numberTex.Release();
}
