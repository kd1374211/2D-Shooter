#pragma once
#include "SceneBase.h"
#include "../Background/Background.h"

class C_Player;

class C_GameScene :public C_SceneBase
{
public:

	C_GameScene();
	~C_GameScene();

	void Update()override;
	void Draw()override;

private:

	C_Background* m_back;
	C_Player* m_player;

};