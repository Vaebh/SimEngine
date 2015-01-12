#ifndef INPUT_MANAGER_SIMENGINE
#define INPUT_MANAGER_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include <map>
#include <list>
#include "../Events/EventMessenger.h"
#include "../Foundation/Foundation.h"
#include <utility>

struct Key
{
	GLint mKeyCode;
	GLint mPreviousState;
};

class InputManager
{
public:
	InputManager(GLFWwindow* inWindow);

	void Init();
	void InitKeys();

	virtual void Update(const float inDT);

	// Prints out mouse coordinates
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);

private:
	void HandleKeyboardInput(const float inDT);
	void HandleKeyInput(Key& inKey, const float inDT);

	void AddKey(const GLint inKeyCode, const uint32_t inPressedEventType, const uint32_t inReleasedEventType);

private:
	GLFWwindow* mWindow;
	GLint mPreviousKeyState;
	uint32_t mPreviousEvent;

	std::vector<Key> mKeys;
	//replace vector with pair
	std::map<GLint, std::pair<uint32_t, uint32_t>> mInputMap;
};

#endif