#ifndef VECTORS_SIMENGINE
#define VECTORS_SIMENGINE

#include "../OpenGL/GLIncludes.h"

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

const Vector3 X_UNIT_POSITIVE(1.f, 0.f, 0.f);
const Vector3 Y_UNIT_POSITIVE(0.f, 1.f, 0.f);
const Vector3 Z_UNIT_POSITIVE(0.f, 0.f, 1.f);

const Vector3 X_UNIT_NEGATIVE(-1.f, 0.f, 0.f);
const Vector3 Y_UNIT_NEGATIVE(0.f, -1.f, 0.f);
const Vector3 Z_UNIT_NEGATIVE(0.f, 0.f, -1.f);

#endif