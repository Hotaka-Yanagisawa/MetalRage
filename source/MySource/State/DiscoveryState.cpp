#include "DiscoveryState.h"
#include "../Enemy.h"
//#include "../Object.h"
//#include "MoveState.h"
#include "FireState.h"

void DiscoveryState::Init(Enemy *obj)
{
	ChangeState(obj, FireState::GetInstance());
}

void DiscoveryState::Update(Enemy *obj)
{
	obj->GetState()->Update(obj, this);
}

void DiscoveryState::ChangeState(Enemy *obj, EnemyState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}