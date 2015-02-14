#include "../Camera/CameraManager.h"

CameraManager::CameraManager() {}
CameraManager::CameraManager(Camera* in_defaultCamera)
{
	AddCamera(in_defaultCamera, true);
}

const int CameraManager::AddCamera(Camera* in_newCamera, bool in_makeActive)
{
	m_cameraVector.push_back(in_newCamera);

	size_t lastIndex = m_cameraVector.size() - 1;

	if(in_makeActive)
	{
		SetActiveCamera(lastIndex);
	}

	return lastIndex;
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
	m_activeCamIndex = in_index;
}

void CameraManager::Update(float in_dt)
{
	for(int i = 0; i < m_cameraVector.size(); ++i)
	{
		m_cameraVector[i]->Update(in_dt);
	}
}