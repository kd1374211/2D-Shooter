#pragma once
#include "../../CharaManagerConst.h"
#include "../../../Const/TextureConst.h"

class C_WeaponBase
{
public: 

	C_WeaponBase() : m_texData(nullptr), m_texScale(Math::Vector2::Zero), m_mat(Math::Matrix::Identity), m_texAngle(0), m_bIsShot(false) {};
	virtual ~C_WeaponBase() {};

	virtual void Update(Math::Vector2 a_playerPos, bool a_isAuto);
	virtual void Draw();

	//発射
	virtual void Shot(Math::Vector2 a_pos);

	//アニメーション
	void UpdateAnimCnt();

protected:

	//画像関連
	S_TexData* m_texData;
	Math::Vector3 m_texScale;
	float m_texAngle;

	Math::Matrix m_mat;

	//発射フラグ
	bool m_bIsShot;
};
