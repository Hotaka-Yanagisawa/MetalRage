#include "TutorialScene.h"
#include "SceneState.h"
#include "../Scene.h"
#include "TutorialState.h"

void TutorialScene::Init(Scene *obj)
{
	ChangeState(obj, TutorialState::GetInstance());
}

void TutorialScene::Uninit(Scene * obj)
{
	obj->GetState()->Uninit(obj);
}

void TutorialScene::Update(Scene * obj)
{
	obj->GetState()->Update(obj, this);
}

void TutorialScene::Draw(Scene *obj)
{
	obj->GetState()->Draw(obj, this);
}

void TutorialScene::ChangeState(Scene * obj, SceneState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}