#pragma once
#include "CharaTexConst.h"
#include "../Const/TextureConst.h"
#include "../Const/ScreenConst.h"

#define TEXSCALE m_texData->m_texScale
#define POSMAX  (MOVEMAX - GetHitRadius())
#define POSMIN  (MOVEMIN + GetHitRadius())

class C_CharaBase
{
public:

	C_CharaBase() :m_texData(nullptr), m_texAngle(0), m_pos(Math::Vector2::Zero), m_move(Math::Vector2::Zero), m_moveSpeed(0) {}
	virtual ~C_CharaBase() {};

	//移動
	void CalcMove();

	virtual void Update();
	virtual void Draw();

	//被弾
	virtual void GetHit();

	//アニメーション
	void UpdateAnimCnt();

	//ゲッター
	Math::Vector2 GetPos()const { return(m_pos); }
	Math::Vector2 GetHitRadius()const { return(m_texData->m_hitSize / 2.0f); }
	S_TexData* GetTexData(E_CharaBaseTexType a_type)const { return(&m_texData->m_texDatas[a_type]); }

protected:

	//画像
	S_BaseCharaTexData* m_texData;
	float m_texAngle;

	//座標
	Math::Vector2 m_pos;

	//移動関連
	Math::Vector2 m_move;
	float m_moveSpeed;

	Math::Matrix m_mat;
};