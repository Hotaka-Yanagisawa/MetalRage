#include "PlayerMove.h"
#include "PlayerJump.h"
#include "../Player.h"
#include "../Defines.h"
#include "../Camera.h"
#include "../Scene.h"
#include "../Input.h"
#include "../Object.h"
#include "../Controller.h"

void PlayerMove::Init(Player * obj)
{
}

void PlayerMove::Update(Player * obj)
{
	//ˆÚ“®ˆ—
	obj->MoveUpdate();
	//ƒWƒƒƒ“ƒv
	if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B, obj->m_PlayerNum))
	{
		obj->m_Parent->SetMove(Float3(obj->m_Parent->GetTransform()->Move.x, 0.2f, obj->m_Parent->GetTransform()->Move.z));
		ChangeState(obj, PlayerJump::GetInstance());
	}
	//”­ŽË
	if (PAD->IsButtonsPress(XINPUT_GAMEPAD_RIGHT_SHOULDER, obj->m_PlayerNum) && !obj->m_bReload && !obj->m_bFire)
		obj->CreateBullet();
	if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_X, obj->m_PlayerNum) && !obj->m_bReload)	obj->Reload();
	if (PAD->IsButtonsPress(XINPUT_GAMEPAD_LEFT_SHOULDER, obj->m_PlayerNum))			obj->Boost();

//#ifndef DEB
	if (IsKeyPress('C') && !obj->m_bReload && !obj->m_bFire)	obj->CreateBullet();
	if (IsKeyTrigger('R') && !obj->m_bReload)					obj->Reload();
	if (IsKeyPress(VK_SHIFT))									obj->Boost();
	if (IsKeyPress(VK_SPACE))
	{
		obj->m_Parent->SetMove
		(Float3(obj->m_Parent->GetTransform()->Move.x,
			0.2f,
			obj->m_Parent->GetTransform()->Move.z));
		ChangeState(obj, PlayerJump::GetInstance());
	}
//#endif
}

void PlayerMove::ChangeState(Player * obj, PlayerState * newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}


