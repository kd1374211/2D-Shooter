#pragma once
#include "../CharaBase.h"

class C_EnemyBase :public C_CharaBase
{
public:

	C_EnemyBase() {};
	~C_EnemyBase() {};

	void Update();
	void Draw();

private:
};