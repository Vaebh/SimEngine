#ifndef CAMERA_SIMENGINE
#define CAMERA_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Structure/Vectors.h"

// TODO - Add Projection matrix to cameras
// TODO - Actually reset m_viewMatrixChanged somewhere, likely after render, add a postRender event?

class Camera
{
public:
	Camera();

	inline const Vector3 GetPosition() const {return m_position;}
	void SetPosition(Vector3 in_position);

	inline const Vector3 GetTarget() const {return m_target;}
	void SetTarget(Vector3 in_target);

	inline const glm::mat4 GetViewMatrix() const {return m_viewMatrix;}

	inline bool HasViewMatrixChanged() const {return m_viewMatrixChanged;}
	inline void ViewMatrixChanged() {m_viewMatrixChanged = !m_viewMatrixChanged;}

	void Update(float in_dt);

private:
	void CalculateViewMatrix();

private:
	bool m_viewMatrixChanged;

	Vector3 m_position;
	Vector3 m_target;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projMatrix;
};

#endif