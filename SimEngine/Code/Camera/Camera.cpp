#include "../Camera/Camera.h"

Camera::Camera() :
m_viewMatrix(glm::mat4()),
m_position(Vector3(1.5f, 1.5f, 1.5f)),
m_target(ZERO),
m_viewMatrixChanged(true)
{
	CalculateViewMatrix();
}

void Camera::SetPosition(Vector3 in_position)
{
	m_position = in_position;

	CalculateViewMatrix();

	m_viewMatrixChanged = true;
}

void Camera::SetTarget(Vector3 in_target)
{
	m_target = in_target;

	CalculateViewMatrix();

	m_viewMatrixChanged = true;
}

void Camera::CalculateViewMatrix()
{
	// Update the view matrix
	m_viewMatrix = glm::lookAt(
		m_position,
		m_target,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Camera::Update(float in_dt)
{

}