////////////////////////////////////////////////////////////////////////////////////////////
// SelectState.h
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

class SelectState :public SceneState
{
public:
	static SelectState *GetInstance()
	{
		static SelectState instance;
		return &instance;
	}

	virtual void Init(Scene *);
	virtual void Uninit(Scene *obj);
	virtual void Update(Scene *, HierarchySceneState *parent);
	virtual void Draw(Scene *, HierarchySceneState *);

private:
	const float m_fInterval = 250;
	//�I�����Ă��������\������|���S��
	void SelectInit();
	void SelectUpdate();
	//�^�C�g���Ƃ��̕����|���S��
	void CharaInit();
	void CharaUpdate();
	void NextScene(Scene *obj);

	ParallelProjection m_SelectPoly[2];	//�����\���|���S��
	ParallelProjection m_CharaPoly[4];	//�^�C�g���Ƃ��̕���
	ParallelProjection m_Push;

	float m_fAlphaCnt;
	bool m_bAlpha;
	
	CSound m_Sound;
	CSound m_SE;
	int m_SelectNum;
	int m_nNextCnt;
	bool m_bNext;

};