#pragma once

class C_Number
{
public:

	void DrawNumber(Math::Vector2 a_pos, int a_number, float a_scale);

private:

	const Math::Vector2 NUMBERSIZE = { 32.0f,64.0f };

	C_Number(){ Init(); }
	~C_Number(){ Release(); }

	void Init();
	void Release();

	KdTexture m_numberTex;

public:

	static C_Number& GetInstance()
	{
		static C_Number instance;
		return instance;
	}

};

#define NUMBER C_Number::GetInstance()