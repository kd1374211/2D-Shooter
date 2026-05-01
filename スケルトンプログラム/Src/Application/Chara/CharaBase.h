#pragma once
#include "CharaTexConst.h"
#include "../Const/TextureConst.h"
#include "../Const/ScreenConst.h"

#define TEXSCALE m_texData.m_texScale

class C_CharaBase
{
public:

	C_CharaBase() :m_texData(S_BaseCharaTexData{}), m_statData(S_CharaStatData{}), m_texAngle(0), m_pos(Math::Vector2::Zero), m_move(Math::Vector2::Zero), m_moveSpeed(0) {}
	virtual ~C_CharaBase() {};

	//移動
	void CalcMove();

	virtual void Update();
	virtual void Draw();

	//被弾
	virtual void GetHit();

	//アニメーション
	virtual void UpdateAnimCnt();

	//ゲッター
	Math::Vector2 GetPos()const { return(m_pos); }
	float GetHitRadius()const { return(m_statData.m_hitRadius); }
	S_TexData* GetTexData(E_CharaBaseTexType a_type) { return(&m_texData.m_texDatas.find(a_type)->second); }

protected:

	//画像
	S_BaseCharaTexData m_texData;
	S_CharaStatData m_statData;
	float m_texAngle;

	//座標
	Math::Vector2 m_pos;

	//移動関連
	Math::Vector2 m_move;
	float m_moveSpeed;

	Math::Matrix m_mat;
};