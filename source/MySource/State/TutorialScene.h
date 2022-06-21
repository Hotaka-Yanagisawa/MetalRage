////////////////////////////////////////////////////////////////////////////////////////////
// TutorialScene.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �`���[�g���A���Ɋւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchySceneState.h"

class TutorialScene : public HierarchySceneState
{
public:
	static TutorialScene *GetInstance()
	{
		static TutorialScene instance;
		return &instance;
	}

	virtual void Init(Scene *obj);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *obj);
	virtual void Draw(Scene *);
	virtual void ChangeState(Scene *obj, SceneState *newState);

};