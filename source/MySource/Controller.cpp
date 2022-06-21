
#include "Controller.h"

Controller::Controller()
{	
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		ZeroMemory(&m_state[i], sizeof(XINPUT_STATE));
		ZeroMemory(&m_oldState[i], sizeof(XINPUT_STATE));
		XInputGetState(i, &m_state[i]);
	}
	//if (dwResult == ERROR_SUCCESS)
	//{
	//	// Controller is connected
	//}
	//else
	//{
	//	// Controller is not connected
	//}
}

Controller::~Controller()
{
}

void Controller::Update()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		m_oldState[i] = m_state[i].Gamepad;
		//ZeroMemory(&m_state[i], sizeof(XINPUT_STATE));
		XInputGetState(i, &m_state[i]);
		//DWORD dwResult = XInputGetState(0, &m_state);
	}


	//if (dwResult == ERROR_SUCCESS)
	//{
	//	// Controller is connected
	//}
	//else
	//{
	//	// Controller is not connected
	//}
}
