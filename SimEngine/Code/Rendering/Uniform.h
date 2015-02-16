#ifndef UNIFORM_SIMENGINE
#define UNIFORM_SIMENGINE

#include "../OpenGL/GLIncludes.h"

class Uniform
{
public:
	Uniform(GLint in_location);

	template<typename T> void Set(T in_v1) const;
	template<typename T> void Set(T in_v1, T in_v2) const;
	template<typename T> void Set(T in_v1, T in_v2, T in_v3) const;
	template<typename T> void Set(T in_v1, T in_v2, T in_v3, T in_v4) const;

	template<typename T> void SetVec(T in_value, GLsizei in_count) const;

	template<typename T> void SetMatrix(T in_value, GLsizei in_count, GLboolean in_transpose) const;

	inline const GLint GetLocation() {return m_location;}

private:
	GLint m_location;
};

#endif