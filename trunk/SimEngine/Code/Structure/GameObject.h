#ifndef GAMEOBJECT_SIMENGINE
#define GAMEOBJECT_SIMENGINE

#include "../Structure/Component.h"
#include "../Structure/Vectors.h"

#include <vector>
#include <string>

class RenderSystem;
class AudioSystem;
class CollisionSystem;
class StateManager;
class InputManager;
class CameraManager;

class IComponent;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Attach(IComponent* in_component);
	void Detach(IComponent* in_component);

	template<class ComponentType>
	ComponentType* GetComponent();

	#pragma region Getters and Setters

	// Position
	inline Vector3 GetPosition() const {return m_position;}
	inline void SetPosition(Vector3 in_position) {m_position = in_position;}
	void MovePosition(Vector3 in_position);
	
	// Scale
	inline Vector3 GetScale() const {return m_scale;}
	inline void SetScale(Vector3 in_scale) {m_scale = in_scale;}
	inline void ScaleBy(Vector3 in_scale) {m_scale += in_scale;}

	// Rotation
	inline glm::quat GetRotation() const {return m_rotationQuat;}
	inline void SetRotation(glm::quat in_rotation) {m_rotationQuat = in_rotation;}

	// Velocity
	inline Vector3 GetVelocity() const {return m_velocity;}
	inline void SetVelocity(Vector3 in_velocity) {m_velocity = in_velocity;}
	inline void MoveVelocity(Vector3 in_velocity) {m_velocity = in_velocity;}

	// Name
	inline const std::string GetName() {return m_name;}
	inline void SetName(std::string in_name) {m_name = in_name;}

	#pragma endregion

	#pragma region System Modules

	inline const RenderSystem* GetRenderSystem() {return m_renderSystem;}
	inline void SetRenderSystem(RenderSystem* in_renderSystem) {m_renderSystem = in_renderSystem;}

	inline const StateManager* GetStateManager() {return m_stateManager;}
	inline void SetStateManager(StateManager* in_stateManager) {m_stateManager = in_stateManager;}

	inline const InputManager* GetInputManager() {return m_inputManager;}
	inline void SetInputManager(InputManager* in_inputManager) {m_inputManager = in_inputManager;}

	inline const AudioSystem* GetAudioSystem() {return m_audioSystem;}
	inline void SetAudioSystem(AudioSystem* in_audioSystem) {m_audioSystem = in_audioSystem;}

	inline const CameraManager* GetCameraManager() {return m_cameraManager;}
	inline void SetCameraManager(CameraManager* in_cameraManager) {m_cameraManager = in_cameraManager;}

	inline const CollisionSystem* GetCollisionSystem() {return m_collisionSystem;}
	inline void SetCollisionSystem(CollisionSystem* in_collisionSystem) {m_collisionSystem = in_collisionSystem;}

	#pragma endregion

	void Update(float in_dt);

public:
	unsigned const int m_index;

	std::vector<IComponent*> m_components;

private:
	static unsigned int m_numGameObjects;

	std::string m_name;

	Vector3 m_position;
	Vector3 m_scale;
	glm::quat m_rotationQuat;

	Vector3 m_velocity;

	// Add getters for all of these
	RenderSystem* m_renderSystem;
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	AudioSystem* m_audioSystem;
	CameraManager* m_cameraManager;
	CollisionSystem* m_collisionSystem;
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