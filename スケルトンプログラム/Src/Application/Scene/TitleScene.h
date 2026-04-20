#pragma once
#include "SceneBase.h"

class C_TitleScene :public C_SceneBase
{
public:

	C_TitleScene();
	~C_TitleScene() {};

	void Update()override;
	void Draw()override;

private:
};