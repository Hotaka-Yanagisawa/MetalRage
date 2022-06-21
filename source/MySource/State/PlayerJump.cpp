#include "PlayerJump.h"
#include "PlayerMove.h"
#include "../Player.h"
#include "../Object.h"
#include "../Defines.h"
#include "../Camera.h"
#include "../Scene.h"
#include "../Input.h"
#include "../Controller.h"

void PlayerJump::Init(Player * obj)
{
	obj->m_bJump = true;
}

void PlayerJump::Update(Player * obj)
{
	//ˆÚ“®ˆ—
	obj->MoveUpdate();
	//”­ŽË
	if (PAD->IsButtonsPress(XINPUT_GAMEPAD_RIGHT_SHOULDER, obj->m_PlayerNum) && !obj->m_bReload && !obj->m_bFire)
		obj->CreateBullet();
	if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_X, obj->m_PlayerNum) && !obj->m_bReload)	obj->Reload();
	//if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER, obj->m_PlayerNum))			obj->Boost();

//#ifndef DEB
	if (IsKeyPress('C') && !obj->m_bReload && !obj->m_bFire)	obj->CreateBullet();
	if (IsKeyTrigger('R') && !obj->m_bReload)					obj->Reload();
	if (IsKeyPress(VK_SHIFT))									obj->Boost();
//#endif

	if (!obj->m_bJump) ChangeState(obj, PlayerMove::GetInstance());
}

void PlayerJump::ChangeState(Player * obj, PlayerState * newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}
