#include "SceneConst.h"
#include "../Chara/Player/Weapon/WeaponConst.h"
#include "../Key/KeyStateManager.h"
#include "SceneManager.h"
#include "../Background/Background.h"
#include "../Fonts/FontManager.h"
#include "../Chara/CharaManager.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/Player/Player.h"

C_SelectScene::C_SelectScene() :m_weaponSelectIndex(E_WeaponName::AutoCannon)
{
	SetSceneTag(E_SceneTypeTag::Select);
	m_back = new C_Background();

	CHARAMGR.SpawnBotPlayer((E_WeaponName)m_weaponSelectIndex, BOTPLAYERPOS);
}

C_SelectScene::~C_SelectScene()
{
	if (m_back)
	{
		delete m_back;
		m_back = nullptr;
	}

	CHARAMGR.DeletePlayer();
	BULLETMGR.ClearBullet();
}

void C_SelectScene::Update()
{
	if (!SCENEMGR.GetIsStop())
	{
		if (KEYMGR.GetKeyState(E_KeyChecks::Right) == E_KeyState::Pressed)
		{
			if (m_weaponSelectIndex < E_WeaponName::BigSpaceGun)
			{
				m_weaponSelectIndex++;
				CHARAMGR.DeletePlayer();
				BULLETMGR.ClearBullet();
				CHARAMGR.SpawnBotPlayer((E_WeaponName)m_weaponSelectIndex, BOTPLAYERPOS);
			}
		}
		else if (KEYMGR.GetKeyState(E_KeyChecks::Left) == E_KeyState::Pressed)
		{
			if (m_weaponSelectIndex > E_WeaponName::AutoCannon)
			{
				m_weaponSelectIndex--;
				CHARAMGR.DeletePlayer();
				BULLETMGR.ClearBullet();
				CHARAMGR.SpawnBotPlayer((E_WeaponName)m_weaponSelectIndex, BOTPLAYERPOS);
			}
		}
		else if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
		{
			SCENEMGR.SpawnTransition(E_SceneTypeTag::Game);
			SCENEMGR.SetSelectedWeapon((E_WeaponName)m_weaponSelectIndex);
		}
	}

	m_back->Update();
	CHARAMGR.Update();
	BULLETMGR.Update();

	BULLETMGR.CheckBulletDelete();
}

void C_SelectScene::Draw()
{
	//背景
	m_back->Draw();
	
	//プレイヤー
	CHARAMGR.Draw();

	//弾
	BULLETMGR.Draw();

	//ステータスウィンドウ
	S_SceneTexData* statWindow = SCENEMGR.GetSceneTexData(E_GameTextures::StatWindow);
	Math::Rectangle rec = { 0,0,(long)statWindow->m_texSize.x,(long)statWindow->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statWindow->m_tex, statWindow->m_texPos.x, statWindow->m_texPos.y, statWindow->m_texDrawSize.x, statWindow->m_texDrawSize.y, &rec);

	std::string name = {};

	//選択武器名
	switch (m_weaponSelectIndex)
	{
	case E_WeaponName::AutoCannon:
		name = "Dual Gun";
		break;
	case E_WeaponName::BigSpaceGun:
		name = "Ball Launcher";
		break;
	default:
		name = "ERROR";
		break;
	}
	FONTMGR.DrawWord({ 0,-50 }, name, 3.0f, Math::Color(1, 1, 1, 1));

	//武器のステータスとバー画像データを持ってくる
	S_SelectWeaponStat stat = SCENEMGR.GetSelectedWeaponStat((E_WeaponName)m_weaponSelectIndex);
	S_SceneTexData* statBar = SCENEMGR.GetSceneTexData(E_GameTextures::StatBar);

	//各ステータス
	FONTMGR.DrawWord({ -250,-140 }, "DAMAGE", 2.0f, Math::Color(1, 1, 1, 1));
	rec = { (long)((WEAPONSTAT_MAX - stat.m_damage) * statBar->m_texSize.x),0,(long)statBar->m_texSize.x,(long)statBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statBar->m_tex, statBar->m_texPos.x, statBar->m_texPos.y, statBar->m_texDrawSize.x, statBar->m_texDrawSize.y, &rec);
	
	FONTMGR.DrawWord({ 0,-140 }, "RATE", 2.0f, Math::Color(1, 1, 1, 1));
	rec = { (long)((WEAPONSTAT_MAX - stat.m_rate) * statBar->m_texSize.x),0,(long)statBar->m_texSize.x,(long)statBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statBar->m_tex, statBar->m_texPos.x + STATDRAWOFS_X, statBar->m_texPos.y, statBar->m_texDrawSize.x, statBar->m_texDrawSize.y, &rec);

	FONTMGR.DrawWord({ 250,-140 }, "SPEED", 2.0f, Math::Color(1, 1, 1, 1));
	rec = { (long)((WEAPONSTAT_MAX - stat.m_speed) * statBar->m_texSize.x),0,(long)statBar->m_texSize.x,(long)statBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statBar->m_tex, statBar->m_texPos.x + 2 * STATDRAWOFS_X, statBar->m_texPos.y, statBar->m_texDrawSize.x, statBar->m_texDrawSize.y, &rec);
}
