////////////////////////////////////////////////////////////////////////////////////////////
// SelectState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// ゲームシーン開始時に関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/24	作成
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
	//選択してるやつを強調表示するポリゴン
	void SelectInit();
	void SelectUpdate();
	//タイトルとかの文字ポリゴン
	void CharaInit();
	void CharaUpdate();
	void NextScene(Scene *obj);

	ParallelProjection m_SelectPoly[2];	//強調表示ポリゴン
	ParallelProjection m_CharaPoly[4];	//タイトルとかの文字
	ParallelProjection m_Push;

	float m_fAlphaCnt;
	bool m_bAlpha;
	
	CSound m_Sound;
	CSound m_SE;
	int m_SelectNum;
	int m_nNextCnt;
	bool m_bNext;

};