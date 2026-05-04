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

	const Math::Vector2 PLAYERSPAWNPOS = { -550,-60.0f };

	//背景
	C_Background* m_back;

};