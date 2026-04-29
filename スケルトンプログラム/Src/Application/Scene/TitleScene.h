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

	const float ALPHACHANGE = 0.02f;
	const float ALPHAMIN = 0.2f;
	const float ALPHAMAX = 1.0f;

	C_Background* m_back = nullptr;
	KdTexture m_titleTex;
	KdTexture m_startButtonTex;
	float m_alpha;
	int m_alphaChangeMulti;

};