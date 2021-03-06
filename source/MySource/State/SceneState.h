////////////////////////////////////////////////////////////////////////////////////////////
// SceneState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// Sceneの状態に関することの抽象クラス
//-----------------------------------------------------------------------------------------
// 2020/12/23	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

class Scene;
class HierarchySceneState;

class SceneState
{
public:
	virtual ~SceneState() {}
	virtual void Init(Scene *) = 0;
	virtual void Uninit(Scene *) = 0;
	virtual void Update(Scene *, HierarchySceneState *) = 0;
	virtual void Draw(Scene *, HierarchySceneState *) = 0;
};