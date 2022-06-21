////////////////////////////////////////////////////////////////////////////////////////////
// HierarchySceneState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// Stateを管理しやすくするため階層ごとに分ける抽象クラス
//-----------------------------------------------------------------------------------------
// 2020/12/23	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

class Scene;
class SceneState;

// 階層用基底状態　　　抽象クラス
class HierarchySceneState
{
public:
	virtual ~HierarchySceneState() {}

	virtual void Init       (Scene *)          = 0;
	virtual void Uninit		(Scene *)		   = 0;
	virtual void Update     (Scene *)          = 0;
	virtual void Draw		(Scene *)		   = 0;
	virtual void ChangeState(Scene *, SceneState *)	= 0;

protected:
};