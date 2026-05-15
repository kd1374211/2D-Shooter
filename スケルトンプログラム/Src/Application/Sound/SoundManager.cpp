#include "SoundManager.h"
#include "../Const/TextureConst.h"

void C_SoundManager::PlayBGM(BGM a_bgm)
{
}

void C_SoundManager::PlaySE(SE a_se)const
{
	//データ
	std::shared_ptr<KdSoundInstance> inst = m_seData[(int)a_se].m_inst;

	//リセット
	StopSE(a_se);

	//再生（ループ無し）
	inst->Play(false);
}

void C_SoundManager::StopBGM(BGM a_bgm)
{}

void C_SoundManager::StopSE(SE a_se)const
{
	//データ
	std::shared_ptr<KdSoundInstance> inst = m_seData[(int)a_se].m_inst;

	//動いていたら停止
	if (inst->IsPlay())inst->Stop();
}

void C_SoundManager::Init()
{
	LoadBGM();
	LoadSE();
}

void C_SoundManager::LoadBGM()
{
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
	for (int i = 0; i < (int)SE::Max; i++)
	{
		if (m_seData[i].m_inst->IsPlay())m_seData[i].m_inst->Stop();
	}
}
