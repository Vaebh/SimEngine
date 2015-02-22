#ifndef MODEL_LOADER_SIMENGINE
#define MODEL_LOADER_SIMENGINE

#include <vector>
#include "../Structure/Vectors.h"
#include "../OpenGL/GLIncludes.h"

bool LoadVertexData(const char* in_fileName, std::vector<GLfloat>& out_vertexData, int& out_numVerts);

bool ConstructVertexData(const char* in_name, const char* in_destPath, const std::vector<Vector3>& in_vertices, const std::vector<glm::vec2>& in_uvs, const std::vector<Vector3>& in_normals);
bool LoadOBJ(std::string in_path, std::vector<Vector3>& out_vertices, std::vector<Vector2>& out_uvs, std::vector<Vector3>& out_normals);
bool LoadOBJRegex(std::string in_path, std::vector<Vector3>& out_vertices, std::vector<Vector2>& out_uvs, std::vector<Vector3>& out_normals);

#endif