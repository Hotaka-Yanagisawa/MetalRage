////////////////////////////////////////////////////////////////////////////////////////////
// StartGameState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �Q�[���V�[���J�n���Ɋւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SceneState.h"
#include "../MySound.h"
#include "../ParallelProjection.h"

class HierarchySceneState;

class StartGameState :public SceneState
{
public:
	static StartGameState *GetInstance()
	{
		static StartGameState instance;
		return &instance;
	}

	virtual void Init(Scene *);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *, HierarchySceneState *parent);
	virtual void Draw(Scene *, HierarchySceneState *);

private:
	CSound m_Sound;
	ParallelProjection m_Push;

	float m_fAlphaCnt;
	bool m_bAlpha;

	int m_nNextCnt;
	bool m_bNext;
};