////////////////////////////////////////////////////////////////////////////////////////////
// GameSceneState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// ゲームシーンに関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchySceneState.h"

class GameScene : public HierarchySceneState
{
public:
	static GameScene *GetInstance()
	{
		static GameScene instance;
		return &instance;
	}

	virtual void Init(Scene *obj);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *obj);
	virtual void Draw(Scene *);
	virtual void ChangeState(Scene *obj, SceneState *newState);

};