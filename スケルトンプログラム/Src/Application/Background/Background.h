#pragma once

class C_Background
{
public:

	C_Background() { Init(); }
	~C_Background() {}

	void Update();
	void Draw();

private:
	
	//背景移動速度
	const float MOVESPEED = 0.75f;

	void Init();
	
	//画像幅
	float m_texWidth;

	//座標
	float m_posX;

	//画像
	std::shared_ptr<KdTexture> m_bgTex;
	std::shared_ptr<KdTexture> m_bgTex2;

};