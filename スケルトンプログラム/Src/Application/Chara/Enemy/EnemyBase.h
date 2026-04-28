#pragma once
#include "../CharaBase.h"

#define SCREENOUT  (SCREENSIZEHALF + GetHitRadius())

class C_EnemyBase :public C_CharaBase
{
public:

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

	void ChangeAction(E_EnemyAction a_action);

	//ゲッター
	bool GetIsEnd()const { return(m_isEnd); }

protected:

	int m_mainAnimCnt;

	int m_health;
	bool m_isEnd;

	E_EnemyAction m_nowAction;
	int m_countF;

};