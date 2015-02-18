#ifndef COMPONENT_SIMENGINE
#define COMPONENT_SIMENGINE

#include "../Structure/GameObject.h"
#include "../Structure/Vectors.h"

class GameObject;
class ISystem;

// TODO - Add a pointer to an ISystem that this component is part of.
// Can either be NULL or a system, upon destruction it will remove 
// itself from the system if it's not NULL
class IComponent
{
public:
    IComponent();
	virtual ~IComponent();

	virtual void Update(float in_dt) = 0;

	inline GameObject* GetOwner() {return m_owner;}
	inline void SetOwner(GameObject* in_newOwner) {m_owner = in_newOwner;}

	virtual void OnAttached(GameObject* in_gameObject);
	virtual void OnDetached(GameObject* in_gameObject);

	inline void SetSystem(ISystem* in_system) {m_system = in_system;}

	virtual void PrePositionSet(Vector3 in_newPosition) {}

protected:
	GameObject* m_owner;

private:
	void RemoveCompFromSystem();

private:
	ISystem* m_system;
};

#endif