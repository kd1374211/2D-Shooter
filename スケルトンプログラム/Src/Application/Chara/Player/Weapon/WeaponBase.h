#pragma once
#include "../../CharaTexConst.h"
#include "../../../Const/TextureConst.h"

class C_WeaponBase
{
public: 

	C_WeaponBase() :m_nameTag(E_WeaponName::WeaponMax), m_texData(nullptr), m_texScale(Math::Vector2::Zero), m_mat(Math::Matrix::Identity), m_texAngle(0) {};
	virtual ~C_WeaponBase() {};

	virtual void Action(Math::Vector2 a_playerPos);
	virtual void Update(Math::Vector2 a_playerPos);
	virtual void Draw();

	//発射
	virtual void Shot(Math::Vector2 a_pos);

	//アニメーション
	void UpdateAnimCnt();

protected:

	//選択武器種
	E_WeaponName m_nameTag;

	//画像関連
	S_TexData* m_texData;
	Math::Vector2 m_texScale;
	float m_texAngle;

	Math::Matrix m_mat;
};
