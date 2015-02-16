#ifndef COMPONENT_SIMENGINE
#define COMPONENT_SIMENGINE

#include "../Structure/GameObject.h"
#include "../Structure/Vectors.h"

class GameObject;

// TODO - Add a pointer to an ISystem that this component is part of.
// Can either be NULL or a system, upon destruction it will remove 
// itself from the system if it's not NULL
class IComponent
{
public:
    IComponent();
	virtual ~IComponent() {}

	virtual void Update(float in_dt) = 0;

	inline GameObject* GetOwner() {return m_owner;}
	inline void SetOwner(GameObject* in_newOwner) {m_owner = in_newOwner;}

	virtual void OnAttached(GameObject* in_gameObject) {}
	virtual void OnDetached(GameObject* in_gameObject) {}

	virtual void PrePositionSet(Vector3 in_newPosition) {}

public:
	GameObject* m_owner;
};

#endif