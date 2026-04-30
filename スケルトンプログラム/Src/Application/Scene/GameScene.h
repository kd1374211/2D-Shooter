#pragma once
#include "SceneBase.h"
#include "../Background/Background.h"

class C_GameScene :public C_SceneBase
{
public:

	C_GameScene();
	~C_GameScene()override;

	void Update()override;
	void Draw()override;

private:

	C_Background* m_back;
	
	KdTexture m_topBarTex;

};