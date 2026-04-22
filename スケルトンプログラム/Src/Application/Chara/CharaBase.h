#pragma once
#include "CharaTexConst.h"

class C_CharaBase
{
public:

	C_CharaBase() :m_texData(nullptr) {};
	~C_CharaBase() {};

	void Action();
	void Update();
	void Draw();

	S_TexData GetData(E_TexType a_type);

protected:

	S_CharaTexData* m_texData;

	Math::Vector2 m_pos;
	Math::Matrix m_mat;
};