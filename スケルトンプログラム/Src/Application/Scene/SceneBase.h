#pragma once
#include "SceneManagerConst.h"

//シーン種
enum class E_SceneTypeTag
{
	Title,
	Select,
	Game,
	Transition,
	Max,
	None = -1
};

class C_SceneBase
{
public:

	C_SceneBase() :m_tag(E_SceneTypeTag::Max) {};
	virtual ~C_SceneBase() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	//セッター
	void SetSceneTag(E_SceneTypeTag a_tag)
	{
		m_tag = a_tag;
	}

	//ゲッター
	E_SceneTypeTag GetSceneTag()const
	{
		return(m_tag);
	}

private:

	//シーン種
	E_SceneTypeTag m_tag;

};