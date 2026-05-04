#pragma once
#include "SceneBase.h"

class C_Background;

class C_ResultScene :public C_SceneBase
{
public:

	C_ResultScene();
	~C_ResultScene()override;

	void Update()override;
	void Draw()override;

private:

	C_Background* m_back;

};