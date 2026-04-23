#pragma once
#include "CharaTexConst.h"

#define TEXSCALE m_texData->m_texScale

class C_CharaBase
{
public:

	C_CharaBase() :m_texData(nullptr), m_angle(0) {};
	virtual ~C_CharaBase() {};

	virtual void Action();
	virtual void Update();
	virtual void Draw();

	//アニメーション
	void UpdateAnimCnt();

	S_TexData GetData(E_TexType a_type);

protected:

	S_CharaTexData* m_texData;

	Math::Vector2 m_pos;
	Math::Matrix m_mat;
	float m_angle;
};