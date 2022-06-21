////////////////////////////////////////////////////////////////////////////////////////////
// ResultState.h
//----------------------------------------------------------------------------------------
// çÏê¨é“ÅFñˆëÚ îøãM
//----------------------------------------------------------------------------------------
// ÉäÉUÉãÉgÇ…ä÷Ç∑ÇÈÇ±Ç∆
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	çÏê¨
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SceneState.h"
#include "../ParallelProjection.h"

class HierarchySceneState;

class ResultState :public SceneState
{
public:
	static ResultState *GetInstance()
	{
		static ResultState instance;
		return &instance;
	}

	virtual void Init(Scene *);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *, HierarchySceneState *parent);
	virtual void Draw(Scene *, HierarchySceneState *);

	ParallelProjection m_Number[2];
	ParallelProjection m_Poly;

private:
	ParallelProjection m_Push;

	float m_fAlphaCnt;
	bool m_bAlpha;
	int m_nNextCnt;
	bool m_bNext;
};