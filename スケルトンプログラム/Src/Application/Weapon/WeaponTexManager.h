#pragma once
#include "WeaponTexConst.h"

class C_WeaponTexManager
{
public:

	void LoadTex();

	S_WeaponTex* GetWeaponTexData(E_WeaponName a_name) { return(&m_weaponTexData[a_name]); }

private:

	static const int STRLENG = 100;

	C_WeaponTexManager() {};
	~C_WeaponTexManager() { ReleaseTex(); }

	void ReleaseTex();

	S_WeaponTex m_weaponTexData[E_WeaponName::WeaponMax];

public:

	static C_WeaponTexManager& GetInstance()
	{
		static C_WeaponTexManager instance;
		return instance;
	}

};

#define WPNTEXMGR C_WeaponTexManager::GetInstance()