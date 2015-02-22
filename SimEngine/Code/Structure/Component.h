#ifndef COMPONENT_SIMENGINE
#define COMPONENT_SIMENGINE

#include "../Structure/Vectors.h"

class GameObject;
class ISystem;

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