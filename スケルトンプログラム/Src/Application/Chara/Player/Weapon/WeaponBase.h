#pragma once
#include "../../CharaTexConst.h"

class C_WeaponBase
{
public: 

	C_WeaponBase() :m_nameTag(E_WeaponName::WeaponMax), m_texData(nullptr), m_scale(Math::Vector2::Zero), m_mat(Math::Matrix::Identity) {};
	~C_WeaponBase() {};

	virtual void Action(Math::Vector2 a_playerPos);
	virtual void Update(Math::Vector2 a_playerPos);
	virtual void Draw();

	virtual void Shot(Math::Vector2 a_pos);

	void UpdateAnimCnt();

protected:

	E_WeaponName m_nameTag;
	S_TexData* m_texData;
	Math::Vector2 m_scale;

	Math::Matrix m_mat;
};
