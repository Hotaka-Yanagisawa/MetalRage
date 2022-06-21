#include "GameScene.h"
#include "SceneState.h"
#include "PvEState.h"
#include "../Scene.h"
#include "StartGameState.h"

void GameScene::Init(Scene *obj)
{
	if (obj->m_Mode ==GAME::PVP)
	{
		ChangeState(obj, StartGameState::GetInstance());
	}
	else
	{
		ChangeState(obj, PvEState::GetInstance());
	}
}

void GameScene::Uninit(Scene * obj)
{
	obj->GetState()->Uninit(obj);
}

void GameScene::Update(Scene *obj)
{
	obj->GetState()->Update(obj, this);
}

void GameScene::Draw(Scene *obj)
{
	obj->GetState()->Draw(obj, this);
}

void GameScene::ChangeState(Scene * obj, SceneState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}