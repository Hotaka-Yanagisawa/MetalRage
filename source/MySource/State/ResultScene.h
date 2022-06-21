////////////////////////////////////////////////////////////////////////////////////////////
// ResultScene.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ���U���g�V�[���Ɋւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/12/23	�쐬
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