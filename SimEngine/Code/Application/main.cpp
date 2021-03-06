/*#include "../Foundation/Foundation.h"

#include "../OpenGL/GLIncludes.h"
#include "../OpenGL/GLUtils.h"

#include "../Input/InputManager.h"
#include "../Rendering/RenderSystem.h"
#include "../Sound/AudioSystem.h"

#include "../Game/StateLevelOne.h"
#include "../Structure/StateManager.h"

#include "../Rendering/Test3DComponent.h"
#include "../Rendering/RenderableMeshComponent.h"
#include "../Rendering/SpriteComponent.h"

#include "../Utils/ModelLoader.h"

#include "../Structure/GameObjectFactory.h"
#include "../Events/EventMessenger.h"
#include "../Camera/CameraManager.h"

#include "../Collision/CollisionSystem.h"

#include <iostream>

using namespace std;

void HandleEvent(uint32_t inEventType, GameObject* inTarget)
{
	inTarget->GetComponent<RenderableMeshComponent>()->SetVisible(false);
}*/

#include "../Application/Application.h"

int main(void)
{
	/*InputManager* inputSystem = new InputManager(RenderSystem::GetSingleton()->mWindow);

	AudioSystem* audioSystem = new AudioSystem();
	audioSystem->Initialise();

	//audioSystem->PlayMusic("Tank.mp3");

	StateManager* stateManager = StateManager::GetSingleton();
	//stateManager->PushState(new StateLevelOne());

	Camera* defaultCam = new Camera();
	CameraManager* camManager = new CameraManager(defaultCam);

	GameObjectFactory* gameObjFactory = new GameObjectFactory(RenderSystem::GetSingleton(), stateManager, inputSystem, audioSystem, camManager, CollisionSystem::GetSingleton());

	/*const std::string imagePath = "../SimEngine/Assets/Models/";

	std::vector<Vector3> tempVertices;
	std::vector<Vector2> tempUVs;
	std::vector<Vector3> tempNormals;
	LoadOBJ(imagePath + "thor.obj", tempVertices, tempUVs, tempNormals);

	std::vector<GLfloat> vertexData;
	ConstructVertexData(vertexData, tempVertices, tempUVs, tempNormals);*/

	// 3D Objects
	/*GameObject* const theCube = gameObjFactory->CreateGameObject();
	theCube->SetScale(Vector3(0.25f, 0.25f, 0.25f));
	
	RenderableMeshComponent* const rendMeshComp = new RenderableMeshComponent("wrong.obj", "bros.png");
	theCube->Attach(rendMeshComp);

	MessageDelegate mesDel = new EventCallbackFree(&HandleEvent);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_PRESS, theCube, mesDel);

	/*GameObject* const theCube2 = new GameObject();
	theCube2->MovePosition(Vector3(0.f, 0.f, 1.2f));
	theCube2->m_scale = Vector3(0.5f, 0.5f, 0.5f);
	
	RenderableMeshComponent* const rendMeshComp2 = new RenderableMeshComponent("sample.png");
	theCube2->Attach(rendMeshComp2);*/

	// Sprite Object
	/*GameObject* const spriteObject = new GameObject();
	spriteObject->SetName("ball");
	spriteObject->SetPosition(Vector3(-0.2, -0.4, 0));
	spriteObject->m_scale = Vector3(0.9, 0.6, 0);

	SpriteComponent* const spriteComp = new SpriteComponent("sample2.png");
	spriteObject->Attach(spriteComp);*/

	/*double olddelta = 0;
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
			//cout << "FPS: " << 1 / delta << endl;
		}

		// Stupid test code
		/*if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_BACKSPACE) == GLFW_PRESS && stateChange == false)
		{
			stateChange = true;
			timer = 0;

			stateManager->PopState();
			stateManager->PushState(new StateLevelOne());
		}*/

		/*static bool keyPressed = false;

		if(!keyPressed && glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			keyPressed = true;
			EventMessenger::GetSingleton()->RecordEvent(INPUT_SPACE_PRESS, theCube);
		}

		if(keyPressed && glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			keyPressed = false;
		}

		if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_COMMA) == GLFW_PRESS)
		{
			defaultCam->SetPosition(defaultCam->GetPosition() + Vector3(0.0001f, 0.f, 0.f));
		}

		theCube->Update(delta);
		//theCube2->Update(delta);
		//spriteObject->Update(delta);

		if(stateChange)
			timer += delta;

		if(timer >= 1)
			stateChange = false;
		// End of stupid test code

		inputSystem->Update(delta);

		//stateManager->Update(delta);

		RenderSystem::GetSingleton()->Draw();

		//glfwSwapBuffers(RenderSystem::mWindow);

		// Check for new events
		glfwPollEvents();
	}

	SAFE_DELETE(inputSystem);
	SAFE_DELETE(audioSystem);
	//SAFE_DELETE(stateManager);

	glfwDestroyWindow(RenderSystem::GetSingleton()->mWindow);
	glfwTerminate();*/

	Application application;

	return 0;
}