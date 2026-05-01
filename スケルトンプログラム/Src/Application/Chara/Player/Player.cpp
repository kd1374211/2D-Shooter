#include "Player.h"
#include "../../Key/KeyStateManager.h"
#include "../CharaManager.h"
#include "Weapon/WeaponConst.h"

C_Player::C_Player(E_WeaponName a_name) :m_weapon(nullptr), m_isInvincible(false)
{
	m_texData = CHARAMGR.GetBaseTexData(E_CharaName::Player);
	m_statData = CHARAMGR.GetStatData(E_CharaName::Player);
	m_selectTexData = CHARAMGR.GetSelectTexData(a_name);
	m_pos = { 0,0 };

	m_texAngle = PLAYERANGLE;
	m_moveSpeed = MOVESPEED;

	switch (a_name)
	{
	case E_WeaponName::AutoCannon:
		m_weapon = new C_AutoCannon(&SELECT.m_texDatas[E_SelectWeaponTexType::Select_Weapon], SELECT.m_texScale);
		break;
	case E_WeaponName::BigSpaceGun:
		m_weapon = new C_BigSpaceGun(&SELECT.m_texDatas[E_SelectWeaponTexType::Select_Weapon], SELECT.m_texScale);
		break;
	}
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

	//画面端
	if (m_pos.x > POSMAX.x)m_pos.x = POSMAX.x;
	else if (m_pos.x < POSMIN.x)m_pos.x = POSMIN.x;

	if (m_pos.y > POSMAX.y)m_pos.y = POSMAX.y;
	else if (m_pos.y < POSMIN.y)m_pos.y = POSMIN.y;

	//攻撃
	m_weapon->Action(m_pos);

	//アニメーション変化
	UpdateAnimCnt();
	UpdateEngineAnim();

	//Matrix
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_texAngle));

	m_mat = rotat * scale * trans;

	m_weapon->Update(m_pos);
}

void C_Player::Draw()
{
	//武器
	m_weapon->Draw();

	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//エンジン
	S_TexData* tex = &SELECT.m_texDatas[E_SelectWeaponTexType::Select_Engine];
	Math::Vector2 texSize = tex->m_texSize;
	Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	//炎
	tex = &SELECT.m_texDatas[E_SelectWeaponTexType::Select_Fire];
	texSize = tex->m_texSize;
	rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	//本体
	tex = GetTexData(E_CharaBaseTexType::Base);
	texSize = tex->m_texSize;
	rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	//無敵
	if (m_isInvincible)
	{
		tex = GetTexData(E_CharaBaseTexType::OnHit);
		texSize = tex->m_texSize;
		rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

		SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);
	}
}

void C_Player::GetHit()
{
	m_isInvincible = true;
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
