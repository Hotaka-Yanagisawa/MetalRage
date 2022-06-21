#pragma once

#include "State/HierarchySceneState.h"

class Camera;
class Collision;
class ParallelProjection;
class Billboard;

namespace GAME
{
	enum MODE
	{
		PVP,
		PVE,
	};
	enum STAGE
	{
		ONE,
		TWO,
		NO,
	};
}

class Scene
{
public:
	static Scene* GetInstance()
	{
		static Scene instance;
		return &instance;
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	SceneState *GetState() { return m_State; }

	void SetState(SceneState *newState) { m_State = newState; }
	void SetHierarchyState(HierarchySceneState *newState)
	{
		m_HierarchyState->Uninit(this);
		m_HierarchyState = newState; 
		m_HierarchyState->Init(this);
	}


	Camera *m_pCamera;
	Camera *m_pCamera2P;
	Collision *m_pCollision;

	ParallelProjection *m_pPolygon;
	GAME::MODE m_Mode;
	GAME::STAGE m_Stage;
private:
	SceneState *m_State;
	HierarchySceneState *m_HierarchyState;


	Scene() {}
	~Scene() {}

};
