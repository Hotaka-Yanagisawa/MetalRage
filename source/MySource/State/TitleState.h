////////////////////////////////////////////////////////////////////////////////////////////
// TitleState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// Titleに関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SceneState.h"
#include "../MySound.h"
#include "../ParallelProjection.h"
#include "../Particle.h"


class HierarchySceneState;



class TitleState :public SceneState
{
public:
	static TitleState *GetInstance()
	{
		static TitleState instance;
		return &instance;
	}

	virtual void Init(Scene *);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *, HierarchySceneState *parent);
	virtual void Draw(Scene *, HierarchySceneState *);

private:
	ParallelProjection m_Push;
	float m_fAlphaCnt;
	bool m_bAlpha;
	ParallelProjection m_Logo;
	Particle m_par;
	CSound m_Sound;
	CSound m_SE;

	int m_nNextCnt;
	bool m_bNext;
};