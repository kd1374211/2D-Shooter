#include "Fighter.h"
#include "../../CharaTexManager.h"
#include "../../../Bullet/BulletManager.h"

C_Fighter::C_Fighter(Math::Vector2 a_pos)
{
	m_pos = a_pos;
	m_moveSpeed = MOVESPEED;
	m_move = { -1,0 };
	m_texData = CHARATEXMGR.GetBaseTexData(E_CharaName::Fighter);
}

void C_Fighter::Update()
{
	m_countF++;
	if (m_countF % ATTACKSPAN == 0)
	{
		ChangeAction(E_EnemyAction::Attack);
	}

	CalcMove();

	//アニメーション変化
	UpdateAnimCnt();

	//攻撃
	if (m_nowAction == E_EnemyAction::Attack)
	{

	}

	//Matrix
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE.x, TEXSCALE.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(m_angle);

	m_mat = rotat * scale * trans;
}

void C_Fighter::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//炎
	S_TexData* tex = GetTexData(E_CharaBaseTexType::EngineEffect);
	Math::Vector2 texSize = tex->m_texSize;
	Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	DrawMainShip();
}
