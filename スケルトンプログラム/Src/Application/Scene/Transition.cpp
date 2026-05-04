#include "Transition.h"
#include "SceneManager.h"

C_Transition::C_Transition(E_SceneTypeTag a_nextScene) :m_isEnd(false), m_countF(0)
{
	m_nextScene = a_nextScene;
}

void C_Transition::Update()
{
	m_countF++;

	if (m_countF == SCENECHANGEF)
	{
		SCENEMGR.SetSceneQueue(m_nextScene);
	}
	else if (m_countF == ENDF)
	{
		m_isEnd = true;
	}
}

void C_Transition::Draw()
{
	//一応リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	//画像用意
	S_SceneTexData* Transition = SCENEMGR.GetSceneTexData(E_GameTextures::Transition);

	Math::Rectangle rec = { 0,0,(long)Transition->m_texSize.x,(long)Transition->m_texSize.y };

	if (m_countF < INENDF)
	{
		int time = INENDF - m_countF;
		SHADER.m_spriteShader.DrawTex(&Transition->m_tex, time * TRANPOSMULTI, 0, Transition->m_texDrawSize.x, Transition->m_texDrawSize.y, &rec);
	}
	else if (m_countF > OUTSTARTF)
	{
		int time = m_countF - OUTSTARTF;
		SHADER.m_spriteShader.DrawTex(&Transition->m_tex, -(time * TRANPOSMULTI), 0, Transition->m_texDrawSize.x, Transition->m_texDrawSize.y, &rec);
	}
	else
	{
		SHADER.m_spriteShader.DrawTex(&Transition->m_tex, 0, 0, Transition->m_texDrawSize.x, Transition->m_texDrawSize.y, &rec);
	}
}
