#pragma once
#include "../EnemyBase.h"

class C_Fighter :public C_EnemyBase
{
public:

	C_Fighter();
	~C_Fighter()override{}

	void Update()override;
	void Draw()override;

private:
};