#include "Scene.h"
#include "State/TitleScene.h"

void Scene::Init()
{
	m_Mode = GAME::PVP;
	m_Stage = GAME::NO;
	m_HierarchyState = TitleScene::GetInstance();
	m_HierarchyState->Init(this);
}

void Scene::Uninit()
{
	m_HierarchyState->Uninit(this);
}

void Scene::Update()
{
	m_HierarchyState->Update(this);

}

void Scene::Draw()
{
	m_HierarchyState->Draw(this);
}
