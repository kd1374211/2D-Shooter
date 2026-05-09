#include "Torpedo.h"
#include "../../CharaManager.h"
#include "../../../Bullet/BulletManager.h"
#include "../../../Time/TimeManager.h"

C_Torpedo::C_Torpedo(Math::Vector2 a_pos) :m_isAttackStart(false), m_isStartBack(false), m_countF_back(0)
{
	m_pos = a_pos;
	m_move = { -1,0 };
	m_texData = CHARAMGR.GetBaseTexData(E_CharaName::Torpedo);
	m_statData = CHARAMGR.GetStatData(E_CharaName::Torpedo);
	m_nowAction = E_EnemyAction::Attack;
	m_moveSpeed = m_statData.m_moveSpeed;
}

void C_Torpedo::Update()
{
	if (!CheckIsDead())
	{
		if (TIMEMGR.GetTimeState() == E_TimeState::Normal || TIMEMGR.GetTimeState() == E_TimeState::Half && TIMEMGR.GetHalfTime())
		{
			//移動
			CalcMove();

			if (m_nowAction == E_EnemyAction::Attack)
			{
				if (m_pos.x <= ATTACKSTARTX && !m_isAttackStart)
				{
					m_isAttackStart = true;
					m_move = Math::Vector2::Zero;
				}

				if (m_isAttackStart)
				{
					for (int i = 0;i < SHOTCOUNT;i++)
					{
						if (GetTexData(E_CharaBaseTexType::Attack)->m_animCnt == SHOTF[i])
						{
							Math::Vector2 bulletPos = { m_pos.x + SHOTPOSOFSX,m_pos.y + SHOTPOSOFSY[i] };
							BULLETMGR.SpawnBullet(bulletPos, BULLETSPEED, BULLETANGLE, E_BulletType::B_Torpedo);
						}
					}
				}
			}
			else if (m_nowAction == E_EnemyAction::Idle)
			{
				m_countF_back++;
				if (m_countF_back >= BACKWAITF && !m_isStartBack)
				{
					m_isStartBack = true;
					m_move = { 1,0 };
				}
			}

			//アニメーション変化
			UpdateAnimCnt();

			//攻撃終了・死亡アニメーション終了
			CheckActionEnd();
		}
	}
	else
	{
		//アニメーション変化
		UpdateAnimCnt();

		//攻撃終了・死亡アニメーション終了
		CheckActionEnd();
	}

	//画面端
	if (m_pos.x > MOVEOUTMAX.x || m_pos.x < MOVEOUTMIN.x)
	{
		m_isEnd = true;
	}
	else if (m_pos.y > MOVEOUTMAX.y || m_pos.y < MOVEOUTMIN.y)
	{
		m_isEnd = true;
	}

	//点滅チェック
	UpdateTexAlpha();

	//Matrix
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_texAngle));

	m_mat = rotat * scale * trans;
}

void C_Torpedo::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//炎（死んでいたら飛ばす）
	if (!CheckIsDead())
	{
		S_TexData* tex = GetTexData(E_CharaBaseTexType::EngineEffect);
		Math::Vector2 texSize = tex->m_texSize;
		Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };
		Math::Color color = { 1,1,1,m_texAlpha };

		SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec, &color);
	}

	DrawMainShip();

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

void C_Torpedo::UpdateAnimCnt()
{
	//炎
	S_TexData* data = GetTexData(E_CharaBaseTexType::EngineEffect);
	data->m_animCnt++;

	if (data->m_animCnt >= data->m_texAnimMax)
	{
		data->m_animCnt -= data->m_texAnimMax;
	}

	//本体
	switch (m_nowAction)
	{
	case E_EnemyAction::Idle:
		data = GetTexData(E_CharaBaseTexType::Base);
		break;
	case E_EnemyAction::Attack:
		if (!m_isAttackStart)return;
		data = GetTexData(E_CharaBaseTexType::Attack);
		break;
	case E_EnemyAction::Dead:
		data = GetTexData(E_CharaBaseTexType::OnHit);
		break;
	}

	data->m_animCnt++;

	if (data->m_animCnt >= data->m_texAnimMax)
	{
		data->m_animCnt -= data->m_texAnimMax;
	}
}

void C_Torpedo::CheckActionEnd()
{
	if (m_nowAction == E_EnemyAction::Attack)
	{
		if (!m_isAttackStart)return;
		if (GetTexData(E_CharaBaseTexType::Attack)->m_animCnt == 0)
		{
			ChangeAction(E_EnemyAction::Idle);
		}
	}
	else if (m_nowAction == E_EnemyAction::Dead)
	{
		if (GetTexData(E_CharaBaseTexType::OnHit)->m_animCnt == 0)
		{
			m_isEnd = true;
		}
	}
}
