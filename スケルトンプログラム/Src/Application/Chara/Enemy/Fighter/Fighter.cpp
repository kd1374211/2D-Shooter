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

	//画面端
	if (fabs(m_pos.x) > SCREENOUT.x)m_isEnd = true;
	else if (fabs(m_pos.y) > SCREENOUT.y)m_isEnd = true;

	//アニメーション変化
	UpdateAnimCnt();

	//攻撃
	if (m_nowAction == E_EnemyAction::Attack)
	{
		if (m_countF % ATTACKSPAN == SHOTF)
		{
			for (int i = 0;i < SHOTCNT;i++)
			{
				BULLETMGR.SpawnBullet(m_pos, BULLETSPEED, SHOTANGLE_BASE + i * SHOTANGLE_DIST, E_BulletType::B_FighterGun);
			}
		}
		else if (m_countF % ATTACKSPAN == ATKENDF)
		{
			ChangeAction(E_EnemyAction::Idle);
		}
	}

	//Matrix
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE.x, TEXSCALE.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));

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
