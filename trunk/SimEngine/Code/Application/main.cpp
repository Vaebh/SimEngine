#include "../Foundation/Foundation.h"

#include "../OpenGL/GLIncludes.h"
#include "../OpenGL/GLUtils.h"

#include "../Input/InputManager.h"
#include "../Rendering/RenderSystem.h"
#include "../Sound/AudioSystem.h"

#include "../Game/StateLevelOne.h"
#include "../Structure/StateManager.h"

#include "../Rendering/Test3DComponent.h"

#include "../Structure/GameObjectFactory.h"

#include <iostream>

using namespace std;

int main(void)
{
	InputManager* inputSystem = new InputManager(RenderSystem::GetSingleton()->mWindow);

	AudioSystem* audioSystem = new AudioSystem();
	audioSystem->Initialise();

	//audioSystem->PlayMusic("Tank.mp3");

	//StateManager* stateManager = StateManager::GetSingleton();
	//stateManager->PushState(new StateLevelOne());


	GameObject* const theCube = new GameObject();

	Test3DComponent* const test3DComp = new Test3DComponent();
	theCube->Attach(test3DComp);

	theCube->SetName("Cube");



	double olddelta = 0;
	double delta = 0;

	float fpsTimer = 0;
	float timer = 0;

	bool stateChange = false;

	// Loop until the window should close
	while (!glfwWindowShouldClose(RenderSystem::GetSingleton()->mWindow))
	{
		delta = glfwGetTime() - olddelta;
		olddelta = glfwGetTime();

		fpsTimer += delta;

		if(fpsTimer > 0.5)
		{
			fpsTimer = 0;
			cout << "FPS: " << 1 / delta << endl;
		}

		// Stupid test code
		/*if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_BACKSPACE) == GLFW_PRESS && stateChange == false)
		{
			stateChange = true;
			timer = 0;

			stateManager->PopState();
			stateManager->PushState(new StateLevelOne());
		}*/

		/*if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_W) == GLFW_PRESS)
		{
			theCube->SetPosition(theCube->GetPosition() + Vector3(0.0f, 0.f, 0.01f));
		}

		if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_S) == GLFW_PRESS)
		{
			theCube->SetPosition(theCube->GetPosition() + Vector3(0.0f, 0.f, -0.01f));
		}

		if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_A) == GLFW_PRESS)
		{
			theCube->SetPosition(theCube->GetPosition() + Vector3(0.0f, -0.01f, 0.f));
		}

		if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_D) == GLFW_PRESS)
		{
			theCube->SetPosition(theCube->GetPosition() + Vector3(0.0f, 0.01f, 0.f));
		}

		if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_Z) == GLFW_PRESS)
		{
			theCube->SetPosition(theCube->GetPosition() + Vector3(-0.01f, 0.f, 0.f));
		}

		if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_X) == GLFW_PRESS)
		{
			theCube->SetPosition(theCube->GetPosition() + Vector3(0.01f, 0.f, 0.f));
		}*/

		theCube->Update(delta);

		if(stateChange)
			timer += delta;

		if(timer >= 1)
			stateChange = false;
		// End of stupid test code

		inputSystem->Update(delta);

		//stateManager->Update(delta);

		RenderSystem::GetSingleton()->Draw();

		glfwSwapBuffers(RenderSystem::mWindow);

		// Check for new events
		glfwPollEvents();
	}

	SAFE_DELETE(inputSystem);
	SAFE_DELETE(audioSystem);
	//SAFE_DELETE(stateManager);

	glfwDestroyWindow(RenderSystem::GetSingleton()->mWindow);
	glfwTerminate();

	return 0;
}