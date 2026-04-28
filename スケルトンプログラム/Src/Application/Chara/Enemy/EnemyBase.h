#pragma once
#include "../CharaBase.h"

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

protected:

	int m_mainAnimCnt;

	int m_health;
	E_EnemyAction m_nowAction;
	int m_countF;

};