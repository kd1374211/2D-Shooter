#pragma once
#include "WeaponTexConst.h"

class C_WeaponBase
{
public: 

	C_WeaponBase() :m_nameTag(E_WeaponName::WeaponMax), m_texData(nullptr), m_mat(Math::Matrix::Identity), m_pos(Math::Vector2::Zero) {};
	~C_WeaponBase() {};

	virtual void Update();
	virtual void Draw();

protected:

	E_WeaponName m_nameTag;
	S_WeaponTex* m_texData;

	Math::Matrix m_mat;
	Math::Vector2 m_pos;

};