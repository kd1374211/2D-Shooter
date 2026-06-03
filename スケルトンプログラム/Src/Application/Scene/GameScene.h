#pragma once
#include "SceneBase.h"
#include "../Background/Background.h"
#include "../Time/TimeManager.h"

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

	void UpdateLevelUpAlpha();
	void ResetLevelUpAlpha();

	void UpdateTimeAura();
	float GetAuraScale();

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
	float m_alphaChangeMulti_timeChargeMax;

	//ガイド消し
	const float DEFAULTGUIDEALPHA = 0.8f;
	const float TRANSPARENTGUIDEALPHA = 0.2f;

	const float GUIDEALPHACHANGE_Y = 170.0f;

	//レベルアップ
	const float MINALPHA_LU = 0.2f;
	const float MAXALPHA_LU = 0.8f;
	const float ALPHACHANGE_LU = 0.03f;

	float m_textAlpha_levelUp;
	float m_alphaChangeMulti_levelUp;

	static const int LEVELUPTEXTF = 60;
	bool m_isLevelUpText;
	int m_countF_levelUp;

	//減速・停止オーラ
	const float AURASCALEMULTI = 0.25f;
	static const int AURASCALEMAXF = 10;

	E_TimeState m_currentState;
	int m_countF_timeState;

	//BGM
	bool m_isStartBGM;
};