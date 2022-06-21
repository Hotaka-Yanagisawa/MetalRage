////////////////////////////////////////////////////////////////////////////////////////////
// PvEState.h
//----------------------------------------------------------------------------------------
// çÏê¨é“ÅFñˆëÚ îøãM
//----------------------------------------------------------------------------------------
// PvEÇ…ä÷Ç∑ÇÈÇ±Ç∆
// 
//-----------------------------------------------------------------------------------------
// 2021/01/09	çÏê¨
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SceneState.h"
#include "../MySound.h"
#include "../ParallelProjection.h"

class HierarchySceneState;
class Object;

class PvEState :public SceneState
{
public:
	static PvEState *GetInstance()
	{
		static PvEState instance;
		return &instance;
	}

	virtual void Init(Scene *);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *, HierarchySceneState *parent);
	virtual void Draw(Scene *, HierarchySceneState *);

	Object *object;
	CSound m_Voice;
	float CreateEnemyTime;
	int NextTime;
	bool m_bNext;
	int m_NextCnt;
	int CntTimer;
	int m_nKillsNum;

	ParallelProjection m_Poly[2];
};