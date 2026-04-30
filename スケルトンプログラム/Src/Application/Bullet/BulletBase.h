#pragma once
#include "BulletTexConst.h"
#include "../Const/TextureConst.h"

class C_BulletBase
{
public:

	C_BulletBase() : m_pos(Math::Vector2::Zero), m_mat(Math::Matrix::Identity), m_team(E_BulletTeam::None), m_texData(nullptr), m_animCnt(0), m_texAngle(0), m_shotAngle(0), m_shotSpeed(0), m_speed(Math::Vector2::Zero) {}
	virtual ~C_BulletBase(){}

	virtual void Update();
	virtual void Draw();

	void UpdateAnimCnt();

	Math::Vector2 GetPos()const { return(m_pos); }

	bool GetIsInScreen();

protected:

	//敵かプレイヤーか
	E_BulletTeam m_team;

	//画像関連
	S_BulletTexData* m_texData;
	int m_animCnt;
	float m_texAngle;

	//座標
	Math::Vector2 m_pos;

	//移動関連
	Math::Vector2 m_speed;
	float m_shotSpeed;
	float m_shotAngle;

	Math::Matrix m_mat;
};