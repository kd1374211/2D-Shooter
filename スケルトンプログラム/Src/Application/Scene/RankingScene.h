#pragma once
#include "SceneBase.h"

class C_Background;

class C_RankingScene :public C_SceneBase
{
public:

	C_RankingScene(E_SceneTypeTag a_scene);
	~C_RankingScene()override;

	void Update()override;
	void Draw()override;

private:

	//背景
	C_Background* m_back;

	//現在ページ
	int m_nowRanking;

	//元居たシーン
	E_SceneTypeTag m_backScene;

	//ランキングの色/場所/サイズ
	static const int RANKINGNUM = 5;

	const float RANKINGPOSX_RANK = -110.0f;
	const float RANKINGPOSX_SCORE = -10.0f;
	const float RANKINGPOSY[RANKINGNUM] = { 120.0f,40.0f,-40.0f,-120.0f,-200.0f };
	float RANKINGSCALE = 3.5f;
	const Math::Color RANKINGCOLOR[RANKINGNUM] = {	Math::Color(0.8f,0.8f,0,1),
													Math::Color(0.9f,0.9f,0.9f,1),
													Math::Color(0.7f,0.2f,0.2f,1),
													Math::Color(0.6f,0.6f,0.6f,1),
													Math::Color(0.6f,0.6f,0.6f,1), };
};
