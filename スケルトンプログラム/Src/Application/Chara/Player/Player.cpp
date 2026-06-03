#include "Player.h"
#include "../../Key/KeyStateManager.h"
#include "../CharaManager.h"
#include "Weapon/WeaponConst.h"
#include "../../Time/TimeManager.h"
#include "../../Sound/SoundManager.h"
#include "../../TimeIcon/TimeIcon.h"

C_Player::C_Player(E_WeaponName a_name, bool a_isBot) :m_weapon(nullptr), m_isInvincible(false), m_isBot(false), m_countF(10), m_invincibleF(0)
{
	m_texData = CHARAMGR.GetBaseTexData(E_CharaName::Player);
	m_statData = CHARAMGR.GetStatData(E_CharaName::Player);
	m_selectTexData = CHARAMGR.GetSelectWeaponData(a_name);
	m_pos = { 0,0 };

	m_texAngle = PLAYERANGLE;
	m_moveSpeed = m_selectTexData.m_moveSpeed;

	switch (a_name)
	{
	case E_WeaponName::AutoCannon:
		m_weapon = new C_AutoCannon(&SELECT.m_texDatas[E_SelectWeaponTexType::Select_Weapon], SELECT.m_texScale);
		break;
	case E_WeaponName::BigSpaceGun:
		m_weapon = new C_BigSpaceGun(&SELECT.m_texDatas[E_SelectWeaponTexType::Select_Weapon], SELECT.m_texScale);
		break;
	}

	//ボット確認
	m_isBot = a_isBot;
}

C_Player::~C_Player()
{
	if (m_weapon)
	{
		delete m_weapon;
		m_weapon = nullptr;
	}
}

void C_Player::Update()
{
	m_move = Math::Vector2::Zero;

	if (!m_isBot)
	{
		//移動
		if (KEYMGR.GetIsPressed(E_KeyChecks::Up))
		{
			m_move.y += 1;
		}
		if (KEYMGR.GetIsPressed(E_KeyChecks::Left))
		{
			m_move.x -= 1;
		}
		if (KEYMGR.GetIsPressed(E_KeyChecks::Down))
		{
			m_move.y -= 1;
		}
		if (KEYMGR.GetIsPressed(E_KeyChecks::Right))
		{
			m_move.x += 1;
		}

		CalcMove();

		//タイムゲージ
		if (TIMEMGR.GetTimeState() == E_TimeState::Normal)
		{
			//シフトを押したとき
			if (KEYMGR.GetKeyState(E_KeyChecks::Shift) == E_KeyState::Pressed)
			{
				//タイムゲージを見る
				if (TIMEMGR.GetTimeCharge() > 0)
				{
					//満タンなら
					if (TIMEMGR.GetTimeCharge() == TIMEMGR.TIMECHARGE_MAX)
					{
						//停止
						TIMEMGR.SetTimeState(E_TimeState::Stop);
						SOUNDMGR.PauseBGM(BGM::Ingame);
						SOUNDMGR.PlaySE(SE::TimeStop);
					}
					else
					{
						//減速
						TIMEMGR.SetTimeState(E_TimeState::Half);
						SOUNDMGR.SlowTime();
					}
				}
			}
		}
		else if (TIMEMGR.GetTimeState() == E_TimeState::Half)
		{
			//シフトを離したとき
			if (KEYMGR.GetKeyState(E_KeyChecks::Shift) == E_KeyState::Released)
			{
				TIMEMGR.SetTimeState(E_TimeState::Normal);
				SOUNDMGR.SlowEnd();
			}
		}

		//減速中なら座標記録
		if (TIMEMGR.GetTimeState() == E_TimeState::Half)
		{
			m_posMemory.push_back(m_pos);
			if (m_posMemory.size() > POSMEMMAX)m_posMemory.erase(m_posMemory.begin());
		}
		else
		{
			if (!m_posMemory.empty())
			{
				m_posMemory.clear();
			}
		}

		//画面端
		if (m_pos.x > POSMAX.x)m_pos.x = POSMAX.x;
		else if (m_pos.x < POSMIN.x)m_pos.x = POSMIN.x;

		if (m_pos.y > POSMAX.y)m_pos.y = POSMAX.y;
		else if (m_pos.y < POSMIN.y)m_pos.y = POSMIN.y;
	}
	else
	{
		m_countF++;

		if (m_countF / TURNF % 2 == 0)
		{
			m_move.y += 1;
		}
		else
		{
			m_move.y -= 1;
		}

		CalcMove();
	}

	if (m_isInvincible)
	{
		m_invincibleF--;

		if (m_invincibleF <= 0)
		{
			m_isInvincible = false;
		}
	}

	//アニメーション変化
	UpdateAnimCnt();
	UpdateEngineAnim();

	//Matrix
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_texAngle));

	m_mat = rotat * scale * trans;

	//武器
	m_weapon->Update(m_pos, m_isBot);
}

void C_Player::Draw()
{
	if (TIMEMGR.GetTimeState() == E_TimeState::Half && !m_posMemory.empty())
	{
		float alpha = 1.0f;
		
		for (int i = 0; i < m_posMemory.size(); i++)
		{
			alpha *= 0.6f;
			Math::Vector2 pos = *(m_posMemory.end() - i - 1);

			//Matrix
			Math::Matrix trans = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
			Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE);
			Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_texAngle));
			SHADER.m_spriteShader.SetMatrix(rotat * scale * trans);

			//本体
			S_TexData* tex = GetTexData(E_CharaBaseTexType::Base);
			Math::Vector2 texSize = tex->m_texSize;
			Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };
			Math::Color color = { 1,1,1,alpha };

			SHADER.m_spriteShader.DrawTex(&(*tex->m_tex), 0, 0, texSize.x, texSize.y, &rec, &color);
		}

		//リセット
		SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	}

	//武器
	m_weapon->Draw();

	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//エンジン
	S_TexData* tex = &SELECT.m_texDatas[E_SelectWeaponTexType::Select_Engine];
	Math::Vector2 texSize = tex->m_texSize;
	Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&(*tex->m_tex), 0, 0, texSize.x, texSize.y, &rec);

	//炎
	tex = &SELECT.m_texDatas[E_SelectWeaponTexType::Select_Fire];
	texSize = tex->m_texSize;
	rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&(*tex->m_tex), 0, 0, texSize.x, texSize.y, &rec);

	//本体
	tex = GetTexData(E_CharaBaseTexType::Base);
	texSize = tex->m_texSize;
	rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&(*tex->m_tex), 0, 0, texSize.x, texSize.y, &rec);

	//無敵
	if (m_isInvincible)
	{
		tex = GetTexData(E_CharaBaseTexType::OnHit);
		texSize = tex->m_texSize;
		rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

		SHADER.m_spriteShader.DrawTex(&(*tex->m_tex), 0, 0, texSize.x, texSize.y, &rec);
	}

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

void C_Player::GetHit()
{
	if (!m_isInvincible)
	{
		m_isInvincible = true;
		TIMEMGR.SubTime(300);
		m_invincibleF = INVINCIBLETIME;
		SOUNDMGR.PlaySE(SE::GetHit);
		TIMEICON.SpawnIcon(m_pos, E_IconType::Minus);
	}
}

void C_Player::UpdateEngineAnim()
{
	S_TexData* data = &SELECT.m_texDatas[E_SelectWeaponTexType::Select_Fire];

	if (data->m_texAnimMax != 1)
	{
		data->m_animCnt++;

		if (data->m_animCnt >= data->m_texAnimMax)
		{
			data->m_animCnt -= data->m_texAnimMax;
		}
	}
}
