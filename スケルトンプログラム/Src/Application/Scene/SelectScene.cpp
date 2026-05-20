#include "SceneConst.h"
#include "../Chara/Player/Weapon/WeaponConst.h"
#include "../Key/KeyStateManager.h"
#include "../Score/ScoreManager.h"
#include "SceneManager.h"
#include "../Background/Background.h"
#include "../Fonts/FontManager.h"
#include "../Chara/CharaManager.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/Player/Player.h"
#include "../Sound/SoundManager.h"

C_SelectScene::C_SelectScene() :m_weaponSelectIndex(SCENEMGR.GetSelectedWeapon()), m_isSelect(false), m_shipFrameAnimCnt(0)
{
	SetSceneTag(E_SceneTypeTag::Select);
	m_back = new C_Background();
	SOUNDMGR.PlayBGM(BGM::Select);

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
				SOUNDMGR.PlaySE(SE::Cursor);
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
				SOUNDMGR.PlaySE(SE::Cursor);
				CHARAMGR.DeletePlayer();
				BULLETMGR.ClearBullet();
				CHARAMGR.SpawnBotPlayer((E_WeaponName)m_weaponSelectIndex, BOTPLAYERPOS);
			}
		}
		else if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
		{
			SCENEMGR.SpawnTransition(E_SceneTypeTag::Game);
			SCENEMGR.SetSelectedWeapon((E_WeaponName)m_weaponSelectIndex);
			m_isSelect = true;
			SOUNDMGR.PlaySE(SE::Enter);
		}
		else if (KEYMGR.GetKeyState(E_KeyChecks::R) == E_KeyState::Pressed)
		{
			SCENEMGR.SpawnTransition(E_SceneTypeTag::Ranking);
			SCENEMGR.SetSelectedWeapon((E_WeaponName)m_weaponSelectIndex);
		}
	}

	//フレームアニメ更新
	m_shipFrameAnimCnt++;
	if (m_shipFrameAnimCnt >= SHIPFRAMEANIMMAX)m_shipFrameAnimCnt -= SHIPFRAMEANIMMAX;

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

	//上のバー
	S_SceneTexData* topBar = SCENEMGR.GetSceneTexData(E_GameTextures::Select_TopBar);
	Math::Rectangle rec = { 0,0,(long)topBar->m_texSize.x,(long)topBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&topBar->m_tex, topBar->m_texPos.x, topBar->m_texPos.y, topBar->m_texDrawSize.x, topBar->m_texDrawSize.y, &rec);

	//ステータスウィンドウ
	S_SceneTexData* statWindow = SCENEMGR.GetSceneTexData(E_GameTextures::Select_StatWindow);
	rec = { 0,0,(long)statWindow->m_texSize.x,(long)statWindow->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statWindow->m_tex, statWindow->m_texPos.x, statWindow->m_texPos.y, statWindow->m_texDrawSize.x, statWindow->m_texDrawSize.y, &rec);

	//現在選択しているキャラ表示用フレーム
	S_SceneTexData* shipFrame = SCENEMGR.GetSceneTexData(E_GameTextures::Select_ShipFrame);
	rec = { (long)((int)(m_shipFrameAnimCnt * SHIPFRAMEANIMMULTI) * shipFrame->m_texSize.x),0,(long)shipFrame->m_texSize.x,(long)shipFrame->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&shipFrame->m_tex, shipFrame->m_texPos.x, shipFrame->m_texPos.y, shipFrame->m_texDrawSize.x, shipFrame->m_texDrawSize.y, &rec);

	//現在選択キャラ
	CHARAMGR.DrawSelectShip(shipFrame->m_texPos, (E_WeaponName)m_weaponSelectIndex);

	//決定ボタン
	S_ButtonPosData* selectButton = nullptr;
	KdTexture* tex = nullptr;
	selectButton = SCENEMGR.GetButtonData(E_GameButtons::Select_Start);

	//決定後かつ決定ボタンを押しているか
	if (m_isSelect && KEYMGR.GetIsPressed(E_KeyChecks::Enter))
	{
		tex = SCENEMGR.GetButtonTex(E_ButtonState::Active);
	}
	else
	{
		tex = SCENEMGR.GetButtonTex(E_ButtonState::Hover);
	}
	rec = { 0,0,(long)BUTTONTEXSIZE.x,(long)BUTTONTEXSIZE.y };
	SHADER.m_spriteShader.DrawTex(tex, selectButton->m_pos.x, selectButton->m_pos.y, selectButton->m_texDrawSize.x, selectButton->m_texDrawSize.y, &rec);

	//矢印
	S_SceneTexData* selectArrow = SCENEMGR.GetSceneTexData(E_GameTextures::Select_Arrow);
	rec = { 0,0,(long)selectArrow->m_texSize.x,(long)selectArrow->m_texSize.y };

	//一番左じゃなければ
	if (m_weaponSelectIndex != E_WeaponName::AutoCannon)
	{
		SHADER.m_spriteShader.DrawTex(&selectArrow->m_tex, -(selectArrow->m_texPos.x), selectArrow->m_texPos.y, -(selectArrow->m_texDrawSize.x), selectArrow->m_texDrawSize.y, &rec);
	}

	//一番右じゃなければ
	if (m_weaponSelectIndex != E_WeaponName::BigSpaceGun)
	{
		SHADER.m_spriteShader.DrawTex(&selectArrow->m_tex, selectArrow->m_texPos.x, selectArrow->m_texPos.y, selectArrow->m_texDrawSize.x, selectArrow->m_texDrawSize.y, &rec);
	}

	//キー色々
	for (auto &itr : SCENEMGR.GetKeyPosData(E_SceneTypeTag::Select))
	{
		S_KeyTexData* data = SCENEMGR.GetKeyTexData(itr.m_key);

		Math::Rectangle rec = { 0,0,(long)data->m_texSize.x ,(long)data->m_texSize.y };
		SHADER.m_spriteShader.DrawTex(&data->m_tex, itr.m_pos.x, itr.m_pos.y, data->m_texDrawSize.x, data->m_texDrawSize.y, &rec);
	}

	//武器のステータスとバー画像データを持ってくる
	S_SelectWeaponStat stat = SCENEMGR.GetSelectedWeaponStat((E_WeaponName)m_weaponSelectIndex);
	S_SceneTexData* statBar = SCENEMGR.GetSceneTexData(E_GameTextures::Select_StatBar);

	//各ステータス
	rec = { (long)((WEAPONSTAT_MAX - stat.m_damage) * statBar->m_texSize.x),0,(long)statBar->m_texSize.x,(long)statBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statBar->m_tex, statBar->m_texPos.x, statBar->m_texPos.y, statBar->m_texDrawSize.x, statBar->m_texDrawSize.y, &rec);
	
	rec = { (long)((WEAPONSTAT_MAX - stat.m_rate) * statBar->m_texSize.x),0,(long)statBar->m_texSize.x,(long)statBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statBar->m_tex, statBar->m_texPos.x + STATDRAWOFS_X, statBar->m_texPos.y, statBar->m_texDrawSize.x, statBar->m_texDrawSize.y, &rec);

	rec = { (long)((WEAPONSTAT_MAX - stat.m_speed) * statBar->m_texSize.x),0,(long)statBar->m_texSize.x,(long)statBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statBar->m_tex, statBar->m_texPos.x + 2 * STATDRAWOFS_X, statBar->m_texPos.y, statBar->m_texDrawSize.x, statBar->m_texDrawSize.y, &rec);

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

	for (auto& itr : SCENEMGR.GetSceneTextsData(E_SceneTypeTag::Select))
	{
		if (itr.m_textTag == E_VariableTextsID::Select_SelectWeapon)
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, name, itr.m_scale, itr.m_color);
		}
		else
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
		}
	}
}
