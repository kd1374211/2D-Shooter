#pragma once
#include "../../CharaTexConst.h"

class C_BulletBase;

class C_WeaponBase
{
public: 

	C_WeaponBase() :m_nameTag(E_WeaponName::WeaponMax), m_texData(nullptr), m_mat(Math::Matrix::Identity) {};
	~C_WeaponBase();

	virtual void Action(Math::Vector2 a_playerPos);
	virtual void Update(Math::Vector2 a_playerPos);
	virtual void Draw();

	virtual void Shot(Math::Vector2 a_pos);

	void UpdateAnimCnt();

	Math::Vector2 GetTexScale() { return(m_texData->m_texScale); }
	S_TexData* GetBulletTex() { return(&m_texData->m_bullet); }

protected:

	E_WeaponName m_nameTag;
	S_WeaponTex* m_texData;

	Math::Matrix m_mat;

	std::vector<C_BulletBase*>m_bullet;
};

#define WEAPON m_texData->m_weapon