#pragma once
#include "SceneBase.h"

class C_SelectScene :public C_SceneBase
{
public:

	C_SelectScene();
	~C_SelectScene()override{}

	void Update()override;
	void Draw()override;

private:

	//選択武器種
	int m_weaponSelectIndex;
};