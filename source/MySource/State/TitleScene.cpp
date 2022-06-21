#include "TitleScene.h"
#include "SceneState.h"
#include "../Scene.h"
#include "TitleState.h"

void TitleScene::Init(Scene *obj)
{
	ChangeState(obj, TitleState::GetInstance());
}

void TitleScene::Uninit(Scene * obj)
{
	obj->GetState()->Uninit(obj);
}

void TitleScene::Update(Scene * obj)
{
	obj->GetState()->Update(obj, this);
}

void TitleScene::Draw(Scene *obj)
{
	obj->GetState()->Draw(obj, this);
}

void TitleScene::ChangeState(Scene * obj, SceneState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}