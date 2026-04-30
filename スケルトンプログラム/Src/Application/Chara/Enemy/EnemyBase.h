#pragma once
#include "../CharaBase.h"

#define SCREENOUT  (SCREENSIZEHALF + GetHitRadius())

class C_EnemyBase :public C_CharaBase
{
public:

	//行動
	enum E_EnemyAction
	{
		Idle,
		Attack,
		Dead
	};

	C_EnemyBase();
	virtual ~C_EnemyBase() {};

	virtual void Update()override;
	virtual void Draw()override;
	void DrawMainShip();

	//被弾
	virtual void GetHit()override;

	//行動
	void ChangeAction(E_EnemyAction a_action);

	//ゲッター
	bool GetIsDead()const;//死亡チェック
	bool GetIsEnd()const { return(m_isEnd); }

protected:

	//アニメーション（本体用）
	int m_mainAnimCnt;

	//体力
	int m_health;

	//消していいかのチェック用
	bool m_isEnd;

	//行動関連
	E_EnemyAction m_nowAction;
	int m_countF;

};