#pragma once
#include "../CharaBase.h"

#define POSMAX  (MOVEMAX - (Math::Vector2)GetHitRadius())
#define POSMIN  (MOVEMIN + (Math::Vector2)GetHitRadius())

class C_WeaponBase;

class C_Player : public C_CharaBase
{
public:

	C_Player(E_WeaponName a_name, bool a_isBot);
	~C_Player()override;

	void Update()	override;
	void Draw()		override;

	//被弾
	void GetHit()override;

	//アニメーション
	void UpdateEngineAnim();

	//ゲッター
	bool GetIsInvincible()const { return(m_isInvincible); }

private:

	//武器とエンジンの画像
	S_PlayerSelectWeaponData m_selectTexData;

	//選択武器
	C_WeaponBase* m_weapon;

	//無敵フラグ
	static const int INVINCIBLETIME = 120;

	bool m_isInvincible;
	int m_invincibleF;

	static const int TURNF = 30;

	//操作可能か
	bool m_isBot;
	int m_countF;
};

#define SELECT m_selectTexData