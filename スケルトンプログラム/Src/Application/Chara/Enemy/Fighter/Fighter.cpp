#include "Fighter.h"
#include "../../CharaManager.h"
#include "../../../Bullet/BulletManager.h"

C_Fighter::C_Fighter(Math::Vector2 a_pos)
{
	m_pos = a_pos;
	m_moveSpeed = MOVESPEED;
	m_move = { -1,0 };
	m_texData = CHARAMGR.GetBaseTexData(E_CharaName::Fighter);
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
	if (m_pos.x > MOVEOUTMAX.x || m_pos.x < MOVEOUTMIN.x)
	{
		m_isEnd = true;
	}
	else if (m_pos.y > MOVEOUTMAX.x || m_pos.y < MOVEOUTMIN.x)
	{
		m_isEnd = true;
	}

	//アニメーション変化
	UpdateAnimCnt();

	//点滅チェック
	UpdateTexAlpha();

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
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_texAngle));

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
	Math::Color color = { 1,1,1,m_texAlpha };

	SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec, &color);

	DrawMainShip();
}
