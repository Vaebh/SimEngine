#ifndef VECTORS_SIMENGINE
#define VECTORS_SIMENGINE

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

const Vector2 VECTOR2_ZERO(0.f, 0.f);
const Vector3 VECTOR3_ZERO(0.f, 0.f, 0.f);
const Vector4 VECTOR4_ZERO(0.f, 0.f, 0.f, 0.f);

const Vector2 X_UNIT_POSITIVE2(1.f, 0.f);
const Vector2 Y_UNIT_POSITIVE2(0.f, 1.f);

const Vector2 X_UNIT_NEGATIVE2(-1.f, 0.f);
const Vector2 Y_UNIT_NEGATIVE2(0.f, -1.f);

const Vector3 X_UNIT_POSITIVE3(1.f, 0.f, 0.f);
const Vector3 Y_UNIT_POSITIVE3(0.f, 1.f, 0.f);
const Vector3 Z_UNIT_POSITIVE3(0.f, 0.f, 1.f);

const Vector3 X_UNIT_NEGATIVE3(-1.f, 0.f, 0.f);
const Vector3 Y_UNIT_NEGATIVE3(0.f, -1.f, 0.f);
const Vector3 Z_UNIT_NEGATIVE3(0.f, 0.f, -1.f);

const Vector4 X_UNIT_POSITIVE4(1.f, 0.f, 0.f, 0.f);
const Vector4 Y_UNIT_POSITIVE4(0.f, 1.f, 0.f, 0.f);
const Vector4 Z_UNIT_POSITIVE4(0.f, 0.f, 1.f, 0.f);
const Vector4 W_UNIT_POSITIVE4(0.f, 0.f, 0.f, 1.f);

const Vector4 X_UNIT_NEGATIVE4(-1.f, 0.f, 0.f, 0.f);
const Vector4 Y_UNIT_NEGATIVE4(0.f, -1.f, 0.f, 0.f);
const Vector4 Z_UNIT_NEGATIVE4(0.f, 0.f, -1.f, 0.f);
const Vector4 W_UNIT_NEGATIVE4(0.f, 0.f, 0.f, -1.f);

#endif