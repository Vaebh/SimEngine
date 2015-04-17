#ifndef COMPONENT_BALL_CONTROLLER_SIMENGINE
#define COMPONENT_BALL_CONTROLLER_SIMENGINE

#include "../Structure/GameObject.h"
#include "../Game/ComponentBallModel.h"
#include "../Foundation/Foundation.h"
#include "../Events/EventMessenger.h"

#include <memory>

class ComponentBallController : public IComponent
{
public:
	ComponentBallController(ComponentBallModel* inBallModel);
	~ComponentBallController();

	void Update(float in_dt);

	void CheckForWindowCollision();

	void HandleEvent(uint32_t inEventType, GameObject* inTarget);

	void LaunchBall();

	void OnAttached(GameObject* inGameObject);
	void OnDetached(GameObject* inGameObject);

	inline void SetAimingObject(GameObject* inAimingObject) {mAimingObject = inAimingObject;}

	//void EnableAimMode();

private:
	ComponentBallModel* mBallModel;
	GameObject* mAimingObject;

	std::unique_ptr<IEventCallback> mCallbackMember;

	bool mAiming;
};

#endif