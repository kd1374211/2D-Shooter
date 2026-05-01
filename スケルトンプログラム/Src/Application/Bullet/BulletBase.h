#pragma once
#include "BulletTexConst.h"
#include "../Const/TextureConst.h"

#define MOVEOUTMAX (MOVEMAX + (Math::Vector2)GetHitRadius())
#define MOVEOUTMIN (MOVEMIN - (Math::Vector2)GetHitRadius())

class C_BulletBase
{
public:

	C_BulletBase() : m_pos(Math::Vector2::Zero), m_mat(Math::Matrix::Identity), m_team(E_BulletTeam::None), m_texData(nullptr), m_animCnt(0), m_texAngle(0), m_shotAngle(0), m_shotSpeed(0), m_speed(Math::Vector2::Zero), m_isEnd(false) {}
	virtual ~C_BulletBase(){}

	virtual void Update();
	virtual void Draw();

	//アニメーション
	void UpdateAnimCnt();

	//セッター
	void SetIsEnd(bool a_isEnd) { m_isEnd = a_isEnd; }

	//ゲッター
	Math::Vector2 GetPos()const { return(m_pos); }
	float GetHitRadius()const { return(m_statData->m_hitRadius); }
	bool GetIsInScreen();//画面内か
	bool GetIsEnd()const { return(m_isEnd); }
	E_BulletTeam GetBulletTeam()const { return(m_team); }

protected:

	//敵かプレイヤーか
	E_BulletTeam m_team;

	//画像関連
	S_BulletTexData* m_texData;
	S_BulletStatData* m_statData;
	int m_animCnt;
	float m_texAngle;

	//座標
	Math::Vector2 m_pos;

	//移動関連
	Math::Vector2 m_speed;
	float m_shotSpeed;
	float m_shotAngle;

	//終了フラグ
	bool m_isEnd;

	Math::Matrix m_mat;
};