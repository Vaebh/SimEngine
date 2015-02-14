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

	void Attach(IComponent* in_component);
	void Detach(IComponent* in_component);

	inline Vector3 GetPosition() const {return m_position;}
	inline void SetPosition(Vector3 in_position) {m_position = in_position;}
	void MovePosition(Vector3 in_position);

	void ScaleBy(Vector3 in_scale) {m_scale += in_scale;}

	inline const std::string GetName() {return m_name;}
	inline void SetName(std::string in_name) {m_name = in_name;}
    
    //void SetOwningScene(Scene* inScene);

	void Update(float in_dt);

	template<class ComponentType>
	ComponentType* GetComponent();

	//inline const RenderSystem* GetRenderSystem() {return m_renderSystem;}

	/*inline const StateManager* GetStateManager() {return m_stateManager;}

	inline const InputManager* GetInputManager() {return m_inputManager;}

	inline const AudioSystem* GetAudioSystem() {return m_audioSystem;}*/

	inline const CameraManager* GetCameraManager() {return m_cameraManager;}
	inline void SetCameraManager(CameraManager* in_cameraManager) {m_cameraManager = in_cameraManager;}

	//inline const CollisionSystem* GetCollisionSystem() {return m_collisionSystem;}

public:
	unsigned const int m_index;
	Vector3 m_scale;
	glm::quat m_rotationQuat;
	Vector3 m_velocity;

	std::vector<IComponent*> m_components;

private:
	static unsigned int m_numGameObjects;

	Vector3 m_position;
	std::string m_name;

	// Add getters for all of these
	/*RenderSystem* m_renderSystem;
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	AudioSystem* m_audioSystem;*/
	CameraManager* m_cameraManager;
	//CollisionSystem* m_collisionSystem;
};

template<class ComponentType>
ComponentType* GameObject::GetComponent()
{
    for(uint32_t i = 0; i < m_components.size(); ++i)
    {
        ComponentType* soughtComp = dynamic_cast<ComponentType*>(m_components[i]);
        
		if(soughtComp != NULL)
		{
			return soughtComp;
		}
    }

	return NULL;
}

#endif