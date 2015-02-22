#include "../Utils/ModelLoader.h"
#include "../Foundation/Foundation.h"
#include "../Foundation/StringUtils.h"

#include <string>
#include <fstream>
#include <iostream>

#include <regex>

bool LoadVertexData(const char* in_fileName, std::vector<GLfloat>& out_vertexData, int& out_numVerts)
{
	std::ifstream inputBinary;
	inputBinary.open(in_fileName, std::ios::in | std::ios::binary | std::ios::ate);
	if(inputBinary.is_open() && inputBinary.good())
	{
		// Get the size of the data in bytes
		std::size_t size = inputBinary.tellg();

		// Subtract an integer worth of bytes as the number of verts is stored in one integer in the file
		size -= sizeof(int);
		inputBinary.seekg(inputBinary.beg);

		out_vertexData.resize(size / sizeof(GLfloat));

		// Read the vertex data directly into the vector
		inputBinary.read((char*)&out_numVerts, sizeof(int));
		inputBinary.read((char*)&out_vertexData[0], size);

		inputBinary.close();

		return true;
	}

	return false;
}

bool ConstructVertexData(const char* in_name, const char* in_destPath, const std::vector<Vector3>& in_vertices, const std::vector<glm::vec2>& in_uvs, const std::vector<Vector3>& in_normals)
{
	if(in_vertices.empty())
		return false;

	std::string fileName(in_destPath);
	fileName.append(in_name);
	fileName.append(".bin");

	std::ofstream outputBinary;
	outputBinary.open(fileName, std::ios::out | std::ios::binary);

	// Write the number of vertices to the file
	int numVertices = in_vertices.size();
	outputBinary.write((char*)&numVertices, sizeof(numVertices));

	for(int i = 0; i < in_vertices.size(); ++i)
	{
		outputBinary.write((char*)&(in_vertices[i].x), sizeof(in_vertices[i].x));
		outputBinary.write((char*)&(in_vertices[i].y), sizeof(in_vertices[i].y));
		outputBinary.write((char*)&(in_vertices[i].z), sizeof(in_vertices[i].z));

		if(in_uvs.empty())
		{
			float zero = 0.f;
			float one = 1.f;

			outputBinary.write((char*)&(zero), sizeof(zero));
			outputBinary.write((char*)&(one), sizeof(one));
		}
		else
		{
			outputBinary.write((char*)&(in_uvs[i].x), sizeof(in_uvs[i].x));
			outputBinary.write((char*)&(in_uvs[i].y), sizeof(in_uvs[i].y));
		}

		if(in_normals.empty())
		{
			float zero = 0.f;

			outputBinary.write((char*)&(zero), sizeof(zero));
			outputBinary.write((char*)&(zero), sizeof(zero));
		}
		else
		{
			float flippedY = in_normals[i].y;
			float flippedZ = in_normals[i].z;
			outputBinary.write((char*)&(in_normals[i].x), sizeof(in_normals[i].x));
			outputBinary.write((char*)&(in_normals[i].y), sizeof(in_normals[i].y));
			outputBinary.write((char*)&(in_normals[i].z), sizeof(in_normals[i].z));
		}
	}

	outputBinary.close();

	return true;
}

bool LoadOBJ(std::string in_path, std::vector<Vector3>& out_vertices, std::vector<Vector2>& out_uvs, std::vector<Vector3>& out_normals)
{
	std::ifstream myFile;
	std::string currentLine;
	char buffer[4096];

	myFile.open(in_path);
	if(myFile.is_open() && !myFile.bad())
	{
		std::vector<glm::vec3> tempVertices;
		std::vector<glm::vec2> tempUVs;
		std::vector<glm::vec3> tempNormals;

		std::vector<std::string> parsedText;

		while(myFile.getline(buffer, 4096))
		{
			currentLine = buffer;

			std::istringstream ss(currentLine);
			std::istream_iterator<std::string> begin(ss), end;
			parsedText = std::vector<std::string>(begin, end);

			if(parsedText.empty())
				continue;

			if(parsedText.front() == "v")
			{
				if(parsedText.size() >= 4)
					tempVertices.push_back(glm::vec3(StringToNumber<float>(parsedText[1]), StringToNumber<float>(parsedText[2]), StringToNumber<float>(parsedText[3])));
			}
			else if(parsedText.front() == "vt")
			{
				if(parsedText.size() >= 3)
					tempUVs.push_back(glm::vec2(StringToNumber<float>(parsedText[1]), 1.f - StringToNumber<float>(parsedText[2])));
			}
			else if(parsedText.front() == "vn")
			{
				if(parsedText.size() >= 4)
					tempNormals.push_back(glm::vec3(StringToNumber<float>(parsedText[1]), StringToNumber<float>(parsedText[2]), StringToNumber<float>(parsedText[3])));
			}
			else if(parsedText.front() == "f")
			{
				std::vector<std::string> parsedFace;
				if(parsedText.size() >= 4)
				{
					if(parsedText[1].find('/') == std::string::npos)
					{
						out_vertices.push_back(tempVertices[StringToNumber<int>(parsedText[1]) - 1]);
						out_vertices.push_back(tempVertices[StringToNumber<int>(parsedText[2]) - 1]);
						out_vertices.push_back(tempVertices[StringToNumber<int>(parsedText[3]) - 1]);
					}
					else
					{
						for(int i = 0; i < parsedText.size(); ++i)
						{
							parsedFace = ParseText(parsedText[i], "/");

							for(int j = 0; j < parsedFace.size(); ++j)
							{
								if(parsedFace[j] == "f")
									continue;

								if(parsedFace[j] == "")
									continue;

								if(j % 3 == 0)
									out_vertices.push_back(tempVertices[StringToNumber<int>(parsedFace[j]) - 1]);
								if(j % 3 == 1)
									out_uvs.push_back(tempUVs[StringToNumber<int>(parsedFace[j]) - 1]);
								if(j % 3 == 2)
									out_normals.push_back(tempNormals[StringToNumber<int>(parsedFace[j]) - 1]);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "File " << in_path << " does not exist!" << std::endl;
		return false;
	}

	return true;
}