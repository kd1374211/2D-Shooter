#pragma once
#include "SceneBase.h"

class C_ResultScene :public C_SceneBase
{
public:

	C_ResultScene() {};
	~C_ResultScene()override {};

	void Update()override;
	void Draw()override;

private:

};