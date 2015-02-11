#ifndef MODEL_LOADER_SIMENGINE
#define MODEL_LOADER_SIMENGINE

#include <vector>
#include "../Structure/Vectors.h"
#include "../OpenGL/GLIncludes.h"

bool ConstructVertexData(std::vector<GLfloat>& out_vertexData, const std::vector<Vector3>& in_vertices, const std::vector<Vector2>& in_uvs, const std::vector<Vector3>& in_normals);
bool LoadOBJ(std::string in_path, std::vector<Vector3>& out_vertices, std::vector<Vector2>& out_uvs, std::vector<Vector3>& out_normals);
bool LoadOBJ2(std::string in_path, std::vector<Vector3>& out_vertices, std::vector<Vector2>& out_uvs, std::vector<Vector3>& out_normals);

#endif