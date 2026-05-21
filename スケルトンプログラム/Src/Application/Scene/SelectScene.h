#pragma once
#include "SceneBase.h"

class C_Background;

class C_SelectScene :public C_SceneBase
{
public:

	C_SelectScene();
	~C_SelectScene()override;

	void Update()override;
	void Draw()override;

private:

	void ResetArrowPos();

	//プレイヤー
	const Math::Vector2 BOTPLAYERPOS = { -580.0f,150.0f };

	//武器の最大ステータス
	static const int WEAPONSTAT_MAX = 5;

	//ステータス描画の位置差
	static const int STATDRAWOFS_X = 250;

	//背景
	C_Background* m_back;

	//選択武器種
	int m_weaponSelectIndex;

	//選択フラグ
	bool m_isSelect;

	//選んでないほうの船の描画位置
	const Math::Vector2 NONSELECTSHIPX = { 120.0f ,0 };

	//フレームのアニメーション
	static const int SHIPFRAMEANIMMAX = 20;
	const float SHIPFRAMEANIMMULTI = 0.2f;

	int m_shipFrameAnimCnt;

	//矢印のアニメーション
	const float ARROWPOSMAX = 8.0f;
	const float ARROWPOSMIN = 0.0f;
	const float ARROWMOVE = 0.5f;

	float m_arrowMoveMulti;
	float m_arrowPos;
};