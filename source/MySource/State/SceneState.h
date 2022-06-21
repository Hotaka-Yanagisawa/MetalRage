////////////////////////////////////////////////////////////////////////////////////////////
// SceneState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// Scene�̏�ԂɊւ��邱�Ƃ̒��ۃN���X
//-----------------------------------------------------------------------------------------
// 2020/12/23	�쐬
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