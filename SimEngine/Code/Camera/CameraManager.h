#ifndef CAM_MANAGER_SIMENGINE
#define CAM_MANAGER_SIMENGINE

#include "../Camera/Camera.h"
#include "../Foundation/Foundation.h"

#include <vector>

class CameraManager
{
public:
	CameraManager();
	CameraManager(Camera* in_defaultCamera);

	const int AddCamera(Camera* in_newCamera, bool in_makeActive = false);
	//const int RemoveCamera(Camera* in_newCamera);

	Camera* GetActiveCamera();
	const Camera* GetActiveCamera() const;
	void SetActiveCamera(const int in_index);

	const Camera* GetCameraAtIndex(int in_camIndex) const;

	void Update(float in_dt);

private:
	int m_activeCamIndex;

	// Might use a stack for this actually
	std::vector<Camera*> m_cameraVector;
};

#endif