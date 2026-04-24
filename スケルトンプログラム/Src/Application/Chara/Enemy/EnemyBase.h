#pragma once
#include "../CharaBase.h"

class C_EnemyBase :public C_CharaBase
{
public:

	C_EnemyBase();
	~C_EnemyBase() {};

	virtual void Action()override;
	virtual void Update()override;
	virtual void Draw()override;

protected:

	int m_health;

};