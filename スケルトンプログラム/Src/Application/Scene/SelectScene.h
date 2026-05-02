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

	//武器の最大ステータス
	static const int WEAPONSTAT_MAX = 5;

	//ステータス描画の位置差
	static const int STATDRAWOFS_X = 250;

	//背景
	C_Background* m_back;

	//選択武器種
	int m_weaponSelectIndex;
};