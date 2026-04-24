#pragma once

class C_Background
{
public:

	C_Background() { Init(); }
	~C_Background() { Release(); }

	void Update();
	void Draw();

private:

	const float MOVESPEED = 6.0f;

	void Init();
	void Release();

	float m_texWidth;
	float m_posX;
	KdTexture m_bgTex;

};