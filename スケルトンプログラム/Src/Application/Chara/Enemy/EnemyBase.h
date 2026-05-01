#pragma once
#include "../CharaBase.h"

#define MOVEOUTMAX (MOVEMAX + (Math::Vector2)GetHitRadius())
#define MOVEOUTMIN (MOVEMIN - (Math::Vector2)GetHitRadius())

class C_EnemyBase :public C_CharaBase
{
public:

	//行動
	enum E_EnemyAction
	{
		Idle,
		Attack,
		Dead
	};

	C_EnemyBase();
	virtual ~C_EnemyBase() {};

	virtual void Update()override;
	virtual void Draw()override;
	void DrawMainShip();

	//点滅
	void UpdateTexAlpha();

	//被弾
	virtual void GetHit(int a_damage);

	//行動
	void ChangeAction(E_EnemyAction a_action);

	//アニメーション
	void UpdateAnimCnt()override;
	void CheckActionEnd();

	bool CheckIsDead()const;//死亡チェック

	//ゲッター
	bool GetIsEnd()const { return(m_isEnd); }

protected:

	//被弾時点滅用
	const float HITALPHA = 0.2f;
	const float ALPHACHANGE = 0.2f;

	float m_texAlpha;

	//体力
	int m_health;

	//消していいかのチェック用
	bool m_isEnd;

	//行動関連
	E_EnemyAction m_nowAction;
	int m_countF;

};