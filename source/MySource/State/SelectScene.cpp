#include "SelectScene.h"
#include "SceneState.h"
#include "../Scene.h"
#include "SelectState.h"

void SelectScene::Init(Scene *obj)
{
	ChangeState(obj, SelectState::GetInstance());
}

void SelectScene::Uninit(Scene * obj)
{
	obj->GetState()->Uninit(obj);
}

void SelectScene::Update(Scene * obj)
{
	obj->GetState()->Update(obj, this);
}

void SelectScene::Draw(Scene *obj)
{
	obj->GetState()->Draw(obj, this);
}

void SelectScene::ChangeState(Scene * obj, SceneState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}