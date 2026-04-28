#pragma once
#include "CharaTexConst.h"
#include "../Const/TextureConst.h"
#include "../Const/ScreenConst.h"

#define TEXSCALE m_texData->m_texScale
#define POSMAX  (SCREENSIZEHALF - GetHitRadius())
#define POSMIN  -(SCREENSIZEHALF - GetHitRadius())

class C_CharaBase
{
public:

	C_CharaBase() :m_texData(nullptr), m_angle(0), m_pos(Math::Vector2::Zero), m_move(Math::Vector2::Zero) {};
	virtual ~C_CharaBase() {};

	virtual void Update();
	virtual void Draw();

	//アニメーション
	void UpdateAnimCnt();

	//ゲッター
	Math::Vector2 GetHitRadius() { return(m_texData->m_hitSize / (2.0f, 2.0f)); };
	S_TexData* GetTexData(E_CharaBaseTexType a_type) { return(&m_texData->m_texDatas[a_type]); }

protected:

	S_BaseCharaTexData* m_texData;

	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix m_mat;
	float m_angle;
};