#include "Player.h"
#include "../../Key/KeyStateManager.h"
#include "../CharaTexManager.h"

C_Player::C_Player() :m_weapon(nullptr)
{
	m_texData = CHARATEXMGR.GetTexData(E_CharaName::Player);
	m_pos = { 0,0 };
}

void C_Player::Action()
{
	//移動
	if (KEYMGR.GetIsPressed(E_KeyChecks::Up))
	{
		m_pos.y += 5;
	}
	if (KEYMGR.GetIsPressed(E_KeyChecks::Left))
	{
		m_pos.x -= 5;
	}
	if (KEYMGR.GetIsPressed(E_KeyChecks::Down))
	{
		m_pos.y -= 5;
	}
	if (KEYMGR.GetIsPressed(E_KeyChecks::Right))
	{
		m_pos.x += 5;
	}

	//攻撃
}

void C_Player::Update()
{
	Math::Matrix scale = Math::Matrix::CreateScale(m_texData->m_texScale.x, m_texData->m_texScale.y, 1);
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);

	m_mat = scale * trans;
}

void C_Player::Draw()
{
	Math::Vector2 texSize = m_texData->m_texSize;

	//本体
	S_TexData tex = GetData(E_TexType::Base);
	Math::Rectangle rec = { (long)((int)(tex.m_animCnt * tex.m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(tex.m_pTex, m_pos.x, m_pos.y, texSize.x, texSize.y, &rec);

	//エンジン
	tex = GetData(E_TexType::Engine);
	rec = { (long)((int)(tex.m_animCnt * tex.m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(tex.m_pTex, m_pos.x, m_pos.y, texSize.x, texSize.y, &rec);

	//炎
	tex = GetData(E_TexType::EngineFire);
	rec = { (long)((int)(tex.m_animCnt * tex.m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(tex.m_pTex, m_pos.x, m_pos.y, texSize.x, texSize.y, &rec);

	//無敵
	tex = GetData(E_TexType::HitImmune);
	rec = { (long)((int)(tex.m_animCnt * tex.m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(tex.m_pTex, m_pos.x, m_pos.y, texSize.x, texSize.y, &rec);
}
