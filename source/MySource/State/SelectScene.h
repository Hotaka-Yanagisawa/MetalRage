////////////////////////////////////////////////////////////////////////////////////////////
// SelectScene.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �Z���N�g�V�[���Ɋւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	�쐬
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