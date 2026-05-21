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

	enum class E_ResultSelectIndex
	{
		PlayAgain,
		Ranking,
		ReturnTitle
	};

private:

	static const int RANKNUM = 5;
	const char* RANKS[RANKNUM] = { "S","A","B","C","D" };
	const Math::Color RANKCOLOR[RANKNUM] =	{	Math::Color(0.9f,0.9f,0,1),
												Math::Color(1.0f,0.2f,0.0f,1),
												Math::Color(0.2f,0,1.0f,1),
												Math::Color(0,1.0f,0.2f,1),
												Math::Color(0.6f,0.6f,0.6f,1) };
	const int RANKTARGET[RANKNUM] = { 20000,16000,12000,6000,0 };

	const Math::Color RESULTCOLOR = Math::Color{ 0.2f,0.9f,0,1 };

	C_Background* m_back;
	
	//時間
	int m_countF;

	//表示タイミング
	static const int TIMEF = 50;
	static const int SCOREF = 80;
	static const int RANKF = 110;
	static const int ENDF = 120;

	//選択ボタン
    int m_nowSelect;

	//選択フラグ
	bool m_isSelect;

	//ランク
	int m_rank;

	//一位かどうか
	bool m_isNewRecord;
};
