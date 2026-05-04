#pragma once
#include "SceneBase.h"

class C_Transition :public C_SceneBase
{
public:

	C_Transition(E_SceneTypeTag a_nextScene);
	~C_Transition() override {}

	void Update()override;
	void Draw()override;

	//終了確認
	bool GetIsEnd()const { return(m_isEnd); }

private:

	//次シーン
	E_SceneTypeTag m_nextScene;

	//時間
	int m_countF;

	//終了フラグ
	bool m_isEnd;

	//演出用const
	static const int INENDF = 10;
	static const int SCENECHANGEF = 10;
	static const int OUTSTARTF = 15;
	static const int ENDF = 25;

	static const int TRANPOSMULTI = 128;
};