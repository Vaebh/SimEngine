#ifndef COMPONENT_SIMENGINE
#define COMPONENT_SIMENGINE

#include "../Structure/GameObject.h"
#include "../Structure/Vectors.h"

class GameObject;

class IComponent
{
public:
    IComponent();
	virtual ~IComponent() {}

	virtual void Update(float inDT) = 0;

	inline GameObject* GetOwner() const {return mOwner;}
	inline void SetOwner(GameObject* inNewOwner) {mOwner = inNewOwner;}

	virtual void OnAttached(GameObject* inGameObject) {}
	virtual void OnDetached(GameObject* inGameObject) {}

	virtual void PrePositionSet(Vector3 inNewPosition) {}

public:
	GameObject* mOwner;
};

#endif