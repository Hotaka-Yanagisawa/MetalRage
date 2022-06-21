////////////////////////////////////////////////////////////////////////////////////////////
// SelectScene.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// セレクトシーンに関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchySceneState.h"

class SelectScene : public HierarchySceneState
{
public:
	static SelectScene *GetInstance()
	{
		static SelectScene instance;
		return &instance;
	}

	virtual void Init(Scene *obj);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *obj);
	virtual void Draw(Scene *);
	virtual void ChangeState(Scene *obj, SceneState *newState);

};