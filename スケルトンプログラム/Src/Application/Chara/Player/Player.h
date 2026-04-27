#pragma once
#include "../CharaBase.h"

class C_WeaponBase;

class C_Player : public C_CharaBase
{
public:

	C_Player(E_WeaponName a_name);
	~C_Player();

	void Action()	override;
	void Update()	override;
	void Draw()		override;

	void UpdateEngineAnim();

private:

	C_WeaponBase* m_weapon;
	S_PlayerSelectTex* m_selectTexData;

};

#define SELECT m_selectTexData