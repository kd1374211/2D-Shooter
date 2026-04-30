#pragma once
#include "../CharaBase.h"

class C_WeaponBase;

class C_Player : public C_CharaBase
{
public:

	C_Player(E_WeaponName a_name);
	~C_Player()override;

	void Update()	override;
	void Draw()		override;

	//被弾
	void GetHit()override;

	//アニメーション
	void UpdateEngineAnim();

private:

	//移動速度
	const float MOVESPEED = 5.0f;

	//武器とエンジンの画像
	S_PlayerSelectTex* m_selectTexData;

	//選択武器
	C_WeaponBase* m_weapon;

	//無敵フラグ
	bool m_isInvincible;

};

#define SELECT m_selectTexData