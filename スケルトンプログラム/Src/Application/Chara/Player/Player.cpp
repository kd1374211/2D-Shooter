#include "Player.h"
#include "../../Key/KeyStateManager.h"
#include "../CharaTexManager.h"
#include "Weapon/WeaponConst.h"

C_Player::C_Player(E_WeaponName a_name) :m_weapon(nullptr)
{
	m_texData = CHARATEXMGR.GetBaseTexData(E_CharaName::Player);
	m_pos = { 0,0 };

	m_angle = PLAYERANGLE;

	m_weapon = new C_AutoCannon();
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

	//攻撃
}

void C_Player::Update()
{
	//アニメーション変化
	UpdateAnimCnt();

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

	//本体
	S_TexData* tex = GetData(E_CharaBaseTexType::Base);
	Math::Vector2 texSize = tex->m_texSize;
	Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);

	//無敵
	//tex = GetData(E_TexType::HitImmune);
	//texSize = tex.m_texSize;
	//rec = { (long)((int)(tex.m_animCnt * tex.m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	//SHADER.m_spriteShader.DrawTex(tex.m_pTex, m_pos.x, m_pos.y, texSize.x * scale.x, texSize.y * scale.y, &rec);
}
