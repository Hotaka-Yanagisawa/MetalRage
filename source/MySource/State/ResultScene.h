////////////////////////////////////////////////////////////////////////////////////////////
// ResultScene.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// リザルトシーンに関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/23	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchySceneState.h"

class ResultScene : public HierarchySceneState
{
public:
	static ResultScene *GetInstance()
	{
		static ResultScene instance;
		return &instance;
	}

	virtual void Init	(Scene *obj);
	virtual void Uninit(Scene *obj);
	virtual void Update	(Scene *obj);
	virtual void Draw(Scene *);
	virtual void ChangeState(Scene *obj, SceneState *newState);

};