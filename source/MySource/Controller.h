#pragma once

#pragma comment (lib, "xinput.lib")

#include <Windows.h>
#include <Xinput.h>

#define PAD (Controller::GetInstance())
#define MAX_PLAYER (2)


//IsButtons�قɂ���̈����ɂȂ���
//XINPUT_GAMEPAD_DPAD_UP          0x0001 �\���L�[�u��v
//XINPUT_GAMEPAD_DPAD_DOWN        0x0002 �\���L�[�u���v
//XINPUT_GAMEPAD_DPAD_LEFT        0x0004 �\���L�[�u���v
//XINPUT_GAMEPAD_DPAD_RIGHT       0x0008 �\���L�[�u�E�v
//XINPUT_GAMEPAD_START            0x0010 START�{�^��
//XINPUT_GAMEPAD_BACK             0x0020 BACK�{�^��
//XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100 LB
//XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200 RB
//XINPUT_GAMEPAD_A                0x1000 A
//XINPUT_GAMEPAD_B                0x2000 B
//XINPUT_GAMEPAD_X                0x4000 X
//XINPUT_GAMEPAD_Y                0x8000 Y

class Controller
{
public:
	static Controller* GetInstance()
	{
		static Controller instance;
		return &instance;
	}

	void Update();

	//LT,RT�p
	bool IsLTriggerPress	(int num = 0) { return m_state[num].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; }
	bool IsRTriggerPress	(int num = 0) { return m_state[num].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; }
	bool IsLTriggerTrigger	(int num = 0) { return (m_state[num].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && XINPUT_GAMEPAD_TRIGGER_THRESHOLD > m_oldState[num].bLeftTrigger) ? true : false; }
	bool IsRTriggerTrigger	(int num = 0) { return (m_state[num].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && XINPUT_GAMEPAD_TRIGGER_THRESHOLD > m_oldState[num].bRightTrigger) ? true : false; }


	//���A�i���O�X�e�B�b�N�p
	bool IsLStickLeft	(int num = 0) { return m_state[num].Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
	bool IsLStickRight	(int num = 0) { return m_state[num].Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE; }
	bool IsLStickDown	(int num = 0) { return m_state[num].Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
	bool IsLStickUp		(int num = 0) { return m_state[num].Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }

	//�E�A�i���O�X�e�B�b�N�p
	bool IsRStickLeft	(int num = 0) { return m_state[num].Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
	bool IsRStickRight	(int num = 0) { return m_state[num].Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE; }
	bool IsRStickDown	(int num = 0) { return m_state[num].Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
	bool IsRStickUp		(int num = 0) { return m_state[num].Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }

	//���̑��{�^���p�iMODE�{�^���͎g��Ȃ����Ɓj
	bool IsButtonsPress		(int nButton, int num = 0) { return m_state[num].Gamepad.wButtons & nButton; }
	bool IsButtonsTrigger	(int nButton, int num = 0) { return (m_state[num].Gamepad.wButtons ^ m_oldState[num].wButtons) & m_state[num].Gamepad.wButtons & nButton; }
	bool IsButtonsRelease	(int nButton, int num = 0) { return (m_state[num].Gamepad.wButtons ^ m_oldState[num].wButtons) & m_oldState[num].wButtons & nButton; }

private:
	Controller();
	~Controller();

	XINPUT_STATE m_state[MAX_PLAYER];
	XINPUT_GAMEPAD m_oldState[MAX_PLAYER];
protected:
	
};

//#pragma once
//
//#pragma comment (lib, "xinput.lib")
//
//#include <Windows.h>
//#include <Xinput.h>
//
//#define PAD (Controller::GetInstance())
//#define MAX_PLAYER (2)
//
//
////IsButtons�قɂ���̈����ɂȂ���
////XINPUT_GAMEPAD_DPAD_UP          0x0001 �\���L�[�u��v
////XINPUT_GAMEPAD_DPAD_DOWN        0x0002 �\���L�[�u���v
////XINPUT_GAMEPAD_DPAD_LEFT        0x0004 �\���L�[�u���v
////XINPUT_GAMEPAD_DPAD_RIGHT       0x0008 �\���L�[�u�E�v
////XINPUT_GAMEPAD_START            0x0010 START�{�^��
////XINPUT_GAMEPAD_BACK             0x0020 BACK�{�^��
////XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100 LB
////XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200 RB
////XINPUT_GAMEPAD_A                0x1000 A
////XINPUT_GAMEPAD_B                0x2000 B
////XINPUT_GAMEPAD_X                0x4000 X
////XINPUT_GAMEPAD_Y                0x8000 Y
//
//class Controller
//{
//public:
//	static Controller* GetInstance()
//	{
//		static Controller instance;
//		return &instance;
//	}
//
//	void Update();
//
//	//LT,RT�p
//	bool IsLTriggerPress() { return m_state[num].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; }
//	bool IsRTriggerPress() { return m_state[num].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; }
//	bool IsLTriggerTrigger() { return (m_state[num].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && XINPUT_GAMEPAD_TRIGGER_THRESHOLD > m_oldState.bLeftTrigger) ? true : false; }
//	bool IsRTriggerTrigger() { return (m_state[num].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && XINPUT_GAMEPAD_TRIGGER_THRESHOLD > m_oldState.bRightTrigger) ? true : false; }
//
//
//	//���A�i���O�X�e�B�b�N�p
//	bool IsLStickLeft() { return m_state[num].Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
//	bool IsLStickRight() { return m_state[num].Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE; }
//	bool IsLStickDown() { return m_state[num].Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
//	bool IsLStickUp() { return m_state[num].Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
//
//	//�E�A�i���O�X�e�B�b�N�p
//	bool IsRStickLeft() { return m_state[num].Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
//	bool IsRStickRight() { return m_state[num].Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE; }
//	bool IsRStickDown() { return m_state[num].Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
//	bool IsRStickUp() { return m_state[num].Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; }
//
//	//���̑��{�^���p�iMODE�{�^���͎g��Ȃ����Ɓj
//	bool IsButtonsPress(int nButton) { return m_state[num].Gamepad.wButtons & nButton; }
//	bool IsButtonsTrigger(int nButton) { return (m_state[num].Gamepad.wButtons ^ m_oldState.wButtons) & m_state[num].Gamepad.wButtons & nButton; }
//	bool IsButtonsRelease(int nButton) { return (m_state[num].Gamepad.wButtons ^ m_oldState.wButtons) & m_oldState.wButtons & nButton; }
//
//private:
//	Controller();
//	~Controller();
//
//	XINPUT_STATE m_state[num];
//	XINPUT_GAMEPAD m_oldState;
//protected:
//
//};


