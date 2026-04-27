#pragma once
#include "BulletTexConst.h"
#include "../Const/TextureConst.h"

class C_BulletBase
{
public:

	C_BulletBase() : m_pos(Math::Vector2::Zero), m_mat(Math::Matrix::Identity), m_team(E_BulletTeam::None), m_texData(nullptr), m_animCnt(0) {}
	virtual ~C_BulletBase(){}

	virtual void Update();
	virtual void Draw();

	void UpdateAnimCnt();

	Math::Vector2 GetPos() { return(m_pos); }

	bool GetIsInScreen();

protected:

	E_BulletTeam m_team;

	S_BulletTexData* m_texData;
	int m_animCnt;

	Math::Vector2 m_pos;
	Math::Matrix m_mat;
};