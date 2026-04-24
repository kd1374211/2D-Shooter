#include "Player.h"
#include "../../Key/KeyStateManager.h"
#include "../CharaTexManager.h"
#include "Weapon/WeaponConst.h"
#include "../../Const/ScreenConst.h"

C_Player::C_Player(E_WeaponName a_name) :m_weapon(nullptr), m_engineTex(nullptr)
{
	m_texData = CHARATEXMGR.GetBaseTexData(E_CharaName::Player);
	m_engineTex = CHARATEXMGR.GetEngineTexData(a_name);
	m_pos = { 0,0 };

	m_angle = PLAYERANGLE;

	switch (a_name)
	{
	case E_WeaponName::AutoCannon:
		m_weapon = new C_AutoCannon();
		break;
	case E_WeaponName::BigSpaceGun:
		m_weapon = new C_BigSpaceGun();
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

	//画面端
	if (m_pos.x > POSMAX.x)m_pos.x = POSMAX.x;
	else if (m_pos.x < POSMIN.x)m_pos.x = POSMIN.x;

	if (m_pos.y > POSMAX.y)m_pos.y = POSMAX.y;
	else if (m_pos.y < POSMIN.y)m_pos.y = POSMIN.y;

	//攻撃
	m_weapon->Action(m_pos);
}

void C_Player::Update()
{
	//アニメーション変化
	UpdateAnimCnt();
	UpdateEngineAnim();

	//Matrix
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(TEXSCALE.x, TEXSCALE.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(m_angle);

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
	S_TexData* tex = &m_engineTex->m_engine;
	Math::Vector2 texSize = tex->m_texSize;
	Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	//炎
	tex = &m_engineTex->m_fire;
	texSize = tex->m_texSize;
	rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	//本体
	tex = GetTexData(E_CharaBaseTexType::Base);
	texSize = tex->m_texSize;
	rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	//無敵
	//tex = GetData(E_TexType::HitImmune);
	//texSize = tex.m_texSize;
	//rec = { (long)((int)(tex.m_animCnt * tex.m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	//SHADER.m_spriteShader.DrawTex(tex.m_pTex, m_pos.x, m_pos.y, texSize.x * scale.x, texSize.y * scale.y, &rec);
}

void C_Player::UpdateEngineAnim()
{
	S_TexData* data = &m_engineTex->m_fire;

	if (data->m_texAnimMax != 1)
	{
		data->m_animCnt++;

		if (data->m_animCnt >= data->m_texAnimMax)
		{
			data->m_animCnt -= data->m_texAnimMax;
		}
	}
}
