#include "PatrolState.h"
#include "../Enemy.h"
#include "MoveState.h"
#include "../Object.h"


void PatrolState::Init(Enemy *obj)
{
	ChangeState(obj, MoveState::GetInstance());
}

void PatrolState::Update(Enemy *obj)
{
	obj->GetState()->Update(obj, this);
}

void PatrolState::ChangeState(Enemy *obj, EnemyState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}
