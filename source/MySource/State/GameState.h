////////////////////////////////////////////////////////////////////////////////////////////
// GameState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// ゲームに関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SceneState.h"
#include "../MySound.h"

class HierarchySceneState;

class GameState :public SceneState
{
public:
	static GameState *GetInstance()
	{
		static GameState instance;
		return &instance;
	}

	virtual void Init(Scene *);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *, HierarchySceneState *parent);
	virtual void Draw(Scene *, HierarchySceneState *);

	int m_nDrawNum;
	bool m_bNext;
	int m_NextCnt;

	int m_nWinner;
	CSound m_Voice;
};
