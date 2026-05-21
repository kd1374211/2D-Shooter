#include "Bomber.h"
#include "../../CharaManager.h"
#include "../../../Time/TimeManager.h"
#include "../../Player/Player.h"

C_Bomber::C_Bomber(Math::Vector2 a_pos) :m_moveAngle(0)
{
	m_pos = a_pos;
	CalcMoveAngle();
	m_texData = CHARAMGR.GetBaseTexData(E_CharaName::Bomber);
	m_statData = CHARAMGR.GetStatData(E_CharaName::Bomber);
	m_moveSpeed = m_statData.m_moveSpeed;
	m_enemyType = E_CharaName::Bomber;
}

void C_Bomber::Update()
{
	if (!CheckIsDead())
	{
		if (TIMEMGR.GetTimeState() == E_TimeState::Normal || TIMEMGR.GetTimeState() == E_TimeState::Half && TIMEMGR.GetHalfTime())
		{
			CalcMove();

			//画面端
			if (m_pos.x > MOVEOUTMAX.x || m_pos.x < MOVEOUTMIN.x)
			{
				m_isEnd = true;
			}
			else if (m_pos.y > MOVEOUTMAX.y || m_pos.y < MOVEOUTMIN.y)
			{
				m_isEnd = true;
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

	//点滅チェック
	UpdateTexAlpha();

	//Matrix
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_moveAngle - m_texAngle));

	m_mat = rotat * scale * trans;
}

void C_Bomber::Draw()
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

		SHADER.m_spriteShader.DrawTex(&(*tex->m_tex), 0, 0, texSize.x, texSize.y, &rec, &color);
	}

	DrawMainShip();

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

void C_Bomber::CalcMoveAngle()
{
	Math::Vector2 playerPos = CHARAMGR.GetPlayer()->GetPos();
	m_moveAngle = DirectX::XMConvertToDegrees(atan2(playerPos.y - m_pos.y, playerPos.x - m_pos.x));
	m_move.x = cosf(DirectX::XMConvertToRadians(m_moveAngle));
	m_move.y = sinf(DirectX::XMConvertToRadians(m_moveAngle));
}
