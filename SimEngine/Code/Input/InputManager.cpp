#include "../Input/InputManager.h"
#include "../Events/EventMessenger.h"

#include <string>
#include <fstream>
#include <iostream>

InputManager::InputManager(GLFWwindow* in_window) :
m_window(in_window)
,m_previousEvent(0)
,m_previousKeyState(0)
{
	Init();
	//LoadInput();
}

void InputManager::Init()
{
	InitKeys();
}

void InputManager::InitKeys()
{
	AddKey(GLFW_KEY_1, INPUT_1_PRESS, INPUT_1_RELEASE);
	AddKey(GLFW_KEY_2, INPUT_2_PRESS, INPUT_2_RELEASE);
	AddKey(GLFW_KEY_3, INPUT_3_PRESS, INPUT_3_RELEASE);
	AddKey(GLFW_KEY_4, INPUT_4_PRESS, INPUT_4_RELEASE);

	AddKey(GLFW_KEY_5, INPUT_5_PRESS, INPUT_5_RELEASE);
	AddKey(GLFW_KEY_6, INPUT_6_PRESS, INPUT_6_RELEASE);
	AddKey(GLFW_KEY_7, INPUT_7_PRESS, INPUT_7_RELEASE);
	AddKey(GLFW_KEY_8, INPUT_8_PRESS, INPUT_8_RELEASE);

	AddKey(GLFW_KEY_9, INPUT_9_PRESS, INPUT_9_RELEASE);
	AddKey(GLFW_KEY_0, INPUT_0_PRESS, INPUT_0_RELEASE);
	AddKey(GLFW_KEY_MINUS, INPUT_MINUS_PRESS, INPUT_MINUS_RELEASE);
	AddKey(GLFW_KEY_EQUAL, INPUT_EQUAL_PRESS, INPUT_EQUAL_RELEASE);
	AddKey(GLFW_KEY_BACKSPACE, INPUT_BACKSPACE_PRESS, INPUT_BACKSPACE_RELEASE);

	AddKey(GLFW_KEY_Q, INPUT_Q_PRESS, INPUT_Q_RELEASE);
	AddKey(GLFW_KEY_W, INPUT_W_PRESS, INPUT_W_RELEASE);
	AddKey(GLFW_KEY_E, INPUT_E_PRESS, INPUT_E_RELEASE);
	AddKey(GLFW_KEY_R, INPUT_R_PRESS, INPUT_R_RELEASE);

	AddKey(GLFW_KEY_T, INPUT_T_PRESS, INPUT_T_RELEASE);
	AddKey(GLFW_KEY_Y, INPUT_Y_PRESS, INPUT_Y_RELEASE);
	AddKey(GLFW_KEY_U, INPUT_U_PRESS, INPUT_U_RELEASE);
	AddKey(GLFW_KEY_I, INPUT_I_PRESS, INPUT_I_RELEASE);

	AddKey(GLFW_KEY_O, INPUT_O_PRESS, INPUT_O_RELEASE);
	AddKey(GLFW_KEY_P, INPUT_P_PRESS, INPUT_P_RELEASE);
	AddKey(GLFW_KEY_LEFT_BRACKET, INPUT_LEFT_BRACKET_PRESS, INPUT_LEFT_BRACKET_RELEASE);
	AddKey(GLFW_KEY_RIGHT_BRACKET, INPUT_RIGHT_BRACKET_PRESS, INPUT_RIGHT_BRACKET_RELEASE);
	AddKey(GLFW_KEY_ENTER, INPUT_ENTER_PRESS, INPUT_ENTER_RELEASE);

	AddKey(GLFW_KEY_A, INPUT_A_PRESS, INPUT_A_RELEASE);
	AddKey(GLFW_KEY_S, INPUT_S_PRESS, INPUT_S_RELEASE);
	AddKey(GLFW_KEY_D, INPUT_D_PRESS, INPUT_D_RELEASE);
	AddKey(GLFW_KEY_F, INPUT_F_PRESS, INPUT_F_RELEASE);

	AddKey(GLFW_KEY_G, INPUT_G_PRESS, INPUT_G_RELEASE);
	AddKey(GLFW_KEY_H, INPUT_H_PRESS, INPUT_H_RELEASE);
	AddKey(GLFW_KEY_J, INPUT_J_PRESS, INPUT_J_RELEASE);
	AddKey(GLFW_KEY_K, INPUT_K_PRESS, INPUT_K_RELEASE);

	AddKey(GLFW_KEY_L, INPUT_L_PRESS, INPUT_L_RELEASE);
	AddKey(GLFW_KEY_SEMICOLON, INPUT_SEMICOLON_PRESS, INPUT_SEMICOLON_RELEASE);
	AddKey(GLFW_KEY_APOSTROPHE, INPUT_APOSTROPHE_PRESS, INPUT_APOSTROPHE_RELEASE);

	AddKey(GLFW_KEY_LEFT_SHIFT, INPUT_LEFT_SHIFT_PRESS, INPUT_LEFT_SHIFT_RELEASE);
	AddKey(GLFW_KEY_BACKSLASH, INPUT_BACKSLASH_PRESS, INPUT_BACKSLASH_RELEASE);
	AddKey(GLFW_KEY_Z, INPUT_Z_PRESS, INPUT_Z_RELEASE);
	AddKey(GLFW_KEY_X, INPUT_X_PRESS, INPUT_X_RELEASE);
	AddKey(GLFW_KEY_C, INPUT_C_PRESS, INPUT_C_RELEASE);

	AddKey(GLFW_KEY_V, INPUT_V_PRESS, INPUT_V_RELEASE);
	AddKey(GLFW_KEY_B, INPUT_B_PRESS, INPUT_B_RELEASE);
	AddKey(GLFW_KEY_N, INPUT_N_PRESS, INPUT_N_RELEASE);
	AddKey(GLFW_KEY_M, INPUT_M_PRESS, INPUT_M_RELEASE);

	AddKey(GLFW_KEY_COMMA, INPUT_COMMA_PRESS, INPUT_COMMA_RELEASE);
	AddKey(GLFW_KEY_PERIOD, INPUT_PERIOD_PRESS, INPUT_PERIOD_RELEASE);
	AddKey(GLFW_KEY_SLASH, INPUT_SLASH_PRESS, INPUT_SLASH_RELEASE);
	AddKey(GLFW_KEY_RIGHT_SHIFT, INPUT_RIGHT_SHIFT_PRESS, INPUT_RIGHT_SHIFT_RELEASE);

	AddKey(GLFW_KEY_LEFT_CONTROL, INPUT_LEFT_CONTROL_PRESS, INPUT_LEFT_CONTROL_RELEASE);
	AddKey(GLFW_KEY_LEFT_ALT, INPUT_LEFT_ALT_PRESS, INPUT_LEFT_ALT_RELEASE);
	AddKey(GLFW_KEY_SPACE, INPUT_SPACE_PRESS, INPUT_SPACE_RELEASE);
	AddKey(GLFW_KEY_RIGHT_ALT, INPUT_RIGHT_ALT_PRESS, INPUT_RIGHT_ALT_RELEASE);
	AddKey(GLFW_KEY_RIGHT_CONTROL, INPUT_RIGHT_CONTROL_PRESS, INPUT_RIGHT_CONTROL_RELEASE);

	AddKey(GLFW_KEY_LEFT, INPUT_LEFT_PRESS, INPUT_LEFT_RELEASE);
	AddKey(GLFW_KEY_DOWN, INPUT_DOWN_PRESS, INPUT_DOWN_RELEASE);
	AddKey(GLFW_KEY_RIGHT, INPUT_RIGHT_PRESS, INPUT_RIGHT_RELEASE);
	AddKey(GLFW_KEY_UP, INPUT_UP_PRESS, INPUT_UP_RELEASE);
}

void InputManager::AddKey(const GLint in_keyCode, const uint32_t in_pressedEventType, const uint32_t in_releasedEventType)
{
	Key theKey;
	theKey.m_keyCode = in_keyCode;
	theKey.m_previousState = GLFW_RELEASE;
	m_keys.push_back(theKey);

	m_inputMap[in_keyCode].first = in_pressedEventType;
	m_inputMap[in_keyCode].second = in_releasedEventType;
}

void InputManager::HandleKeyInput(Key& in_key, const float in_dt)
{
	int keyInputState = glfwGetKey(m_window, in_key.m_keyCode);

	if(keyInputState == GLFW_PRESS || // && in_key.m_previousState != GLFW_PRESS) ||
		keyInputState == GLFW_RELEASE)// && in_key.m_previousState != GLFW_RELEASE)
	{
		if(keyInputState == GLFW_PRESS)// && m_previousEvent != m_inputMap[in_key.m_keyCode].first)
		{
			//EventMessenger::GetSingleton()->BroadcastEvent(m_inputMap[inKey.m_keyCode].first);
			EventMessenger::GetSingleton()->RecordEvent(m_inputMap[in_key.m_keyCode].first, NULL);
			m_previousEvent = m_inputMap[in_key.m_keyCode].first;
			in_key.m_previousState = keyInputState;
		}
		else if(keyInputState == GLFW_RELEASE)// && m_previousEvent != m_inputMap[in_key.m_keyCode].second)
		{
			EventMessenger::GetSingleton()->RecordEvent(m_inputMap[in_key.m_keyCode].second, NULL);
     		//EventMessenger::GetSingleton()->BroadcastEvent(m_inputMap[inKey.m_keyCode].second);
			m_previousEvent = m_inputMap[in_key.m_keyCode].second;
			in_key.m_previousState = keyInputState;
		}
	}
}

void InputManager::HandleKeyboardInput(const float in_dt)
{
	for(int i = 0; i < m_keys.size(); ++i)
	{
		HandleKeyInput(m_keys[i], in_dt);
	}
}

void InputManager::Update(const float in_dt)
{
	HandleKeyboardInput(in_dt);
}

bool InputManager::IsKeyDown(const GLint in_keyCode)
{
	return glfwGetKey(m_window, in_keyCode);
}

bool InputManager::IsKeyUp(const GLint in_keyCode)
{
	return !glfwGetKey(m_window, in_keyCode);
}