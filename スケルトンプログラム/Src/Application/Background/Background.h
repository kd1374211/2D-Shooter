#pragma once

class C_Background
{
public:

	C_Background() { Init(); }
	~C_Background() { Release(); }

	void Update();
	void Draw();

private:
	
	//背景移動速度
	const float MOVESPEED = 6.0f;

	void Init();
	void Release();

	//画像幅
	float m_texWidth;

	//座標
	float m_posX;

	//画像
	KdTexture m_bgTex;

};