#include "ResultScene.h"
#include "SceneState.h"
#include "../Scene.h"
#include "ResultState.h"

void ResultScene::Init(Scene *obj)
{
	ChangeState(obj, ResultState::GetInstance());
}

void ResultScene::Uninit(Scene * obj)
{
	obj->GetState()->Uninit(obj);
}

void ResultScene::Update(Scene * obj)
{
	obj->GetState()->Update(obj, this);
}

void ResultScene::Draw(Scene *obj)
{
	obj->GetState()->Draw(obj, this);
}

void ResultScene::ChangeState(Scene * obj, SceneState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}