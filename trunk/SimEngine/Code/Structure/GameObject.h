#ifndef GAMEOBJECT_SIMENGINE
#define GAMEOBJECT_SIMENGINE

class State;

#include "../Structure/Component.h"
//#include "../Structure/Scene.h"
#include "../Structure/Vectors.h"

/*#include "../Rendering/RenderSystem.h"
#include "../Sound/AudioSystem.h"
#include "../Collision/CollisionSystem.h"*/

//#include "../Structure/State.h"
//#include "../Input/InputManager.h"
#include "../Camera/CameraManager.h"

#include <vector>
#include <string>

class ISystem;
class IComponent;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Attach(IComponent* inComponent);
	void Detach(IComponent* inComponent);

	inline Vector3 GetPosition() const {return mPosition;}
	inline void SetPosition(Vector3 inPosition) {mPosition = inPosition;}
	void MovePosition(Vector3 inPosition);

	void ScaleBy(Vector3 inScale) {mScale += inScale;}

	inline const std::string GetName() {return mName;}
	inline void SetName(std::string inName) {mName = inName;}
    
    //void SetOwningScene(Scene* inScene);

	void Update(float inDT);

	template<class ComponentType>
	ComponentType* GetComponent();

	//inline const RenderSystem* GetRenderSystem() {return m_renderSystem;}

	/*inline const StateManager* GetStateManager() {return m_stateManager;}

	inline const InputManager* GetInputManager() {return m_inputManager;}

	inline const AudioSystem* GetAudioSystem() {return m_audioSystem;}

	inline const CameraManager* GetCameraManager() {return m_cameraManager;}

	inline const CollisionSystem* GetCollisionSystem() {return m_collisionSystem;}*/

public:
	unsigned const int mIndex;
	Vector3 mScale;
	Vector3 mRotationAngle;
	Vector3 mVelocity;

	std::vector<IComponent*> mComponents;

private:
	static unsigned int mNumGameObjects;

	Vector3 mPosition;
	std::string mName;

	// Add getters for all of these
	/*RenderSystem* m_renderSystem;
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	AudioSystem* m_audioSystem;
	CameraManager* m_cameraManager;
	CollisionSystem* m_collisionSystem;*/
};

template<class ComponentType>
ComponentType* GameObject::GetComponent()
{
    for(uint32_t i = 0; i < mComponents.size(); ++i)
    {
        ComponentType* soughtComp = dynamic_cast<ComponentType*>(mComponents[i]);
        
		if(soughtComp != NULL)
		{
			return soughtComp;
		}
    }

	return NULL;
}

#endif