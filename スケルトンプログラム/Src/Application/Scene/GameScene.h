#pragma once
#include "SceneBase.h"
#include "../Background/Background.h"

class C_GameScene :public C_SceneBase
{
public:

	C_GameScene();
	~C_GameScene()override;

	void Update()override;
	void Draw()override;

	void UpdateTimeColor();
	void UpdateTimeChargeAlpha();
	void ResetTimeChargeAlpha();

private:

	const Math::Vector2 PLAYERSPAWNPOS = { -550,-60.0f };

	static const int ENEMYMAXLEVEL = 4;
	const Math::Color LEVELCOLOR[ENEMYMAXLEVEL] = { Math::Color(1,1,1,1),
													Math::Color(0.93f,0.7f,0.6f,1),
													Math::Color(0.86f,0.4f,0.2f,1),
													Math::Color(0.8f,0.2f,0,1) };

	//背景
	C_Background* m_back;

	Math::Color m_timeColor;

	const float MINALPHA_TCM = 0.4f;
	const float MAXALPHA_TCM = 1.0f;
	const float ALPHACHANGE_TCM = 0.03f;
	float m_textAlpha_timeChargeMax;
	float m_textAlphaChangeMulti;
};