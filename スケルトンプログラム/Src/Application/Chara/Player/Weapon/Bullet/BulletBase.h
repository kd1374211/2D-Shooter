#pragma once
#include "../../../CharaTexConst.h"

class C_BulletBase
{
public:

	C_BulletBase() :m_tex(nullptr), m_texScale(Math::Vector2::Zero), m_pos(Math::Vector2::Zero), m_mat(Math::Matrix::Identity) {}
	virtual ~C_BulletBase(){}

	virtual void Action();
	virtual void Update();
	virtual void Draw();

	void UpdateAnimCnt();

protected:

	S_TexData* m_tex;
	Math::Vector2 m_texScale;

	Math::Vector2 m_pos;
	Math::Matrix m_mat;
};