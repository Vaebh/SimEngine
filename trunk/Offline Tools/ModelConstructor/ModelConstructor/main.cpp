#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>

template <typename T>
T StringToNumber (std::string& in_text)
{
    std::istringstream ss(in_text);
    T result;
    return ss >> result ? result : 0;
}

std::vector<std::string> ParseText(std::string in_text, std::string in_delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<std::string> delimitedStrings;

	while ((pos = in_text.find(in_delimiter)) != std::string::npos) 
	{
		token = in_text.substr(0, pos);
		delimitedStrings.push_back(token);
		in_text.erase(0, pos + in_delimiter.length());
	}

	delimitedStrings.push_back(in_text);

	return delimitedStrings;
}

bool LoadOBJ(std::string in_path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals);
bool ConstructVertexData(const char* in_name, const char* in_destPath, const std::vector<glm::vec3>& in_vertices, const std::vector<glm::vec2>& in_uvs, const std::vector<glm::vec3>& in_normals);

int main(int argc, char* argv[])
{
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;

	LoadOBJ(argv[1], tempVertices, tempUVs, tempNormals);

	std::vector<std::string> parsedFile = ParseText(argv[1], "/");

	std::string fileName(ParseText(parsedFile.back(), ".")[0]);
	ConstructVertexData(fileName.c_str(), argv[2], tempVertices, tempUVs, tempNormals);
}

bool ConstructVertexData(const char* in_name, const char* in_destPath, const std::vector<glm::vec3>& in_vertices, const std::vector<glm::vec2>& in_uvs, const std::vector<glm::vec3>& in_normals)
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

bool LoadOBJ(std::string in_path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
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