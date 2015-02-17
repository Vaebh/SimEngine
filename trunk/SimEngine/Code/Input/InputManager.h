#ifndef INPUT_MANAGER_SIMENGINE
#define INPUT_MANAGER_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Foundation/Foundation.h"

#include <map>
#include <vector>
#include <utility>

// TODO - Add a circular buffer that stores the last n actions, n being configurable.
// TODO - Add the ability to poll the InputManager directly for input - eg if(keyIsDown)
// TODO - Add an alias to each key so users can specify what they want each to be - eg Jump or Shoot

struct Key
{
	GLint m_keyCode;
	GLint m_previousState;
};

class InputManager
{
public:
	InputManager(GLFWwindow* in_window);

	void Init();
	void InitKeys();

	void Update(const float in_dt);

	bool IsKeyDown(const GLint in_keyCode);
	bool IsKeyUp(const GLint in_keyCode);

	// Prints out mouse coordinates
	static void mouseCallback(GLFWwindow* in_window, int in_button, int in_action, int in_mods);

private:
	void HandleKeyboardInput(const float in_dt);
	void HandleKeyInput(Key& inKey, const float in_dt);

	void AddKey(const GLint in_keyCode, const uint32_t in_pressedEventType, const uint32_t in_releasedEventType);

private:
	GLFWwindow* m_window;
	GLint m_previousKeyState;
	uint32_t m_previousEvent;

	std::vector<Key> m_keys;
	std::map<GLint, std::pair<uint32_t, uint32_t>> m_inputMap;
};

#endif