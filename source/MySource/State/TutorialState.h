////////////////////////////////////////////////////////////////////////////////////////////
// TutorialState.h
//----------------------------------------------------------------------------------------
// çÏê¨é“ÅFñˆëÚ îøãM
//----------------------------------------------------------------------------------------
// TutorialÇ…ä÷Ç∑ÇÈÇ±Ç∆
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	çÏê¨
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SceneState.h"
#include "../ParallelProjection.h"
#include "../MySound.h"

class HierarchySceneState;
class Object;

class TutorialState :public SceneState
{
public:
	static TutorialState *GetInstance()
	{
		static TutorialState instance;
		return &instance;
	}

	virtual void Init(Scene *);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *, HierarchySceneState *parent);
	virtual void Draw(Scene *, HierarchySceneState *);

	void TutorialUpdate();
private:
	int m_nNextCnt;
	bool m_bNext;
	bool m_bEnd;
	ParallelProjection m_Poly[8];
	bool m_bClear[8];
	bool m_bCreate;

	Object *object;

	CSound m_Sound;
	CSound m_Voice;
};