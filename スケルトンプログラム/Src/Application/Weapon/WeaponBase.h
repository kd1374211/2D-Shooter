#pragma once
#include "WeaponTexConst.h"

class C_WeaponBase
{
public: 

	C_WeaponBase() :m_nameTag(E_WeaponName::WeaponMax), m_texData(nullptr), m_mat(Math::Matrix::Identity) {};
	~C_WeaponBase() {};

	virtual void Update(Math::Vector2 a_playerPos);
	virtual void Draw();

	void UpdateAnimCnt();

protected:

	E_WeaponName m_nameTag;
	S_WeaponTex* m_texData;

	Math::Matrix m_mat;
	
	int m_animCnt;

};

#define WEAPON m_texData->m_weapon