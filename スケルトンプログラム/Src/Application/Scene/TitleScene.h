#pragma once
#include "SceneBase.h"

class C_Background;

class C_TitleScene :public C_SceneBase
{
public:

	C_TitleScene();
	~C_TitleScene()override;

	void Update()override;
	void Draw()override;

private:

	//スタートボタンの透明化
	const float ALPHACHANGE = 0.02f;
	const float ALPHAMIN = 0.2f;
	const float ALPHAMAX = 1.0f;

	//背景
	C_Background* m_back = nullptr;

	//タイトル画像関連
	KdTexture m_titleTex;
	KdTexture m_startButtonTex;
	float m_alpha;
	int m_alphaChangeMulti;

};