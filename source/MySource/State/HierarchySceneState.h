////////////////////////////////////////////////////////////////////////////////////////////
// HierarchySceneState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// State���Ǘ����₷�����邽�ߊK�w���Ƃɕ����钊�ۃN���X
//-----------------------------------------------------------------------------------------
// 2020/12/23	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

class Scene;
class SceneState;

// �K�w�p����ԁ@�@�@���ۃN���X
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