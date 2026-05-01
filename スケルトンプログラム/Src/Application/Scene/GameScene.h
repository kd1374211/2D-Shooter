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

	//背景
	C_Background* m_back;
	
	//上のバー（仮）
	KdTexture m_topBarTex;
	KdTexture m_topBarBackTex;

};