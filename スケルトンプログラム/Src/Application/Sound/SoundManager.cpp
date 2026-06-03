#include "SoundManager.h"
#include "../Const/TextureConst.h"

void C_SoundManager::PlayBGM(BGM a_bgm)const
{
	//リセット
	StopBGM();

	//データ
	std::shared_ptr<KdSoundInstance> inst = m_bgmData[(int)a_bgm].m_inst;

	//再生（ループあり）
	inst->Play(true);
}

void C_SoundManager::PlaySE(SE a_se)const
{
	//リセット
	StopSE(a_se);

	//データ
	std::shared_ptr<KdSoundInstance> inst = m_seData[(int)a_se].m_inst;

	//再生（ループ無し）
	inst->Play(false);
}

void C_SoundManager::SlowTime()
{
	m_bgmData[(int)BGM::Ingame].m_inst->SetVolume(INGAMEBGMVOL_SLOW);
}

void C_SoundManager::SlowEnd()
{
	m_bgmData[(int)BGM::Ingame].m_inst->SetVolume(INGAMEBGMVOL);
}

void C_SoundManager::StopBGM()const
{
	for (int i = 0; i < (int)BGM::Max; i++)
	{
		if (m_bgmData[i].m_inst->IsPlay())m_bgmData[i].m_inst->Stop();
	}
}

void C_SoundManager::StopSE(SE a_se)const
{
	//データ
	std::shared_ptr<KdSoundInstance> inst = m_seData[(int)a_se].m_inst;

	//動いていたら停止
	if (inst->IsPlay())inst->Stop();
}

void C_SoundManager::Reset()
{
	SlowEnd();
}

void C_SoundManager::Init()
{
	LoadBGM();
	LoadSE();
}

void C_SoundManager::LoadBGM()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Sound/BackGroundMusicData.csv", "r") == 0)
	{
		char dummy[STRLENG] = {};

		for (int i = 0; i < (int)BGM::Max; i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, STRLENG, fp) != nullptr)//1行読み
			{
				//準備
				m_bgmData[i].m_sound = std::make_shared<KdSoundEffect>();

				char path[STRLENG] = {};
				float volume;

				fscanf_s(fp, "%[^,],%[^,],%f,",
					name, STRLENG,
					path, STRLENG,
					&volume
				);

				//音ロード
				m_bgmData[i].m_sound->Load(path);

				//音セット
				m_bgmData[i].m_inst = m_bgmData[i].m_sound->CreateInstance(false);

				//音量
				m_bgmData[i].m_inst->SetVolume(volume);
			}
		}

		fclose(fp);
	}
}

void C_SoundManager::LoadSE()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Sound/SoundEffectData.csv", "r") == 0)
	{
		char dummy[STRLENG] = {};

		for (int i = 0; i < (int)SE::Max; i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, STRLENG, fp) != nullptr)//1行読み
			{
				//準備
				m_seData[i].m_sound = std::make_shared<KdSoundEffect>();

				char path[STRLENG] = {};
				float volume;

				fscanf_s(fp, "%[^,],%[^,],%f,",
					name, STRLENG,
					path, STRLENG,
					&volume
				);

				//音ロード
				m_seData[i].m_sound->Load(path);

				//音セット
				m_seData[i].m_inst = m_seData[i].m_sound->CreateInstance(false);

				//音量
				m_seData[i].m_inst->SetVolume(volume);
			}
		}

		fclose(fp);
	}
}

void C_SoundManager::StopAll()
{
	StopBGM();

	for (int i = 0; i < (int)SE::Max; i++)
	{
		if (m_seData[i].m_inst->IsPlay())m_seData[i].m_inst->Stop();
	}
}
