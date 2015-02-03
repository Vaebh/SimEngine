#include "../Camera/CameraManager.h"

CameraManager::CameraManager() {}
CameraManager::CameraManager(Camera in_defaultCamera) {}

const int CameraManager::AddCamera(Camera in_newCamera, bool in_makeActive)
{
	return 0;
}

const Camera* CameraManager::GetActiveCamera() const
{
	return m_cameraVector[m_activeCamIndex];
}
const Camera* CameraManager::GetCameraAtIndex(int in_camIndex) const
{
	return m_cameraVector[in_camIndex];
}

void CameraManager::SetActiveCamera(const int in_index)
{

}