#include "../Utils/ModelLoader.h"
#include "../Foundation/Foundation.h"
#include "../Foundation/StringUtils.h"

#include <string>
#include <fstream>
#include <iostream>

#include <regex>

bool ConstructVertexData(std::vector<GLfloat>& out_vertexData, const std::vector<Vector3>& in_vertices, const std::vector<Vector2>& in_uvs, const std::vector<Vector3>& in_normals)
{
	if(in_vertices.empty())
		return false;

	for(int i = 0; i < in_vertices.size(); ++i)
	{
		out_vertexData.push_back(in_vertices[i].x);
		out_vertexData.push_back(in_vertices[i].y);
		out_vertexData.push_back(in_vertices[i].z);

		if(in_uvs.empty())
		{
			out_vertexData.push_back(0.f);
			out_vertexData.push_back(1.f);
		}
		else
		{
			out_vertexData.push_back(in_uvs[i].x);
			out_vertexData.push_back(in_uvs[i].y);
		}
	}

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
		std::vector<Vector3> tempVertices;
		std::vector<Vector2> tempUVs;
		std::vector<Vector3> tempNormals;

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
					tempVertices.push_back(Vector3(StringToNumber<float>(parsedText[1]), StringToNumber<float>(parsedText[2]), StringToNumber<float>(parsedText[3])));
			}
			else if(parsedText.front() == "vt")
			{
				if(parsedText.size() >= 3)
					tempUVs.push_back(Vector2(StringToNumber<float>(parsedText[1]), 1.f - StringToNumber<float>(parsedText[2])));
			}
			else if(parsedText.front() == "vn")
			{
				if(parsedText.size() >= 4)
					tempNormals.push_back(Vector3(StringToNumber<float>(parsedText[1]), StringToNumber<float>(parsedText[2]), StringToNumber<float>(parsedText[3])));
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
								//if(j % 3 == 2)
									//out_normals.push_back(tempNormals[StringToNumber<int>(parsedFace[j]) - 1]);
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

bool LoadOBJRegex(std::string in_path, std::vector<Vector3>& out_vertices, std::vector<Vector2>& out_uvs, std::vector<Vector3>& out_normals)
{
	const uint32_t BUFFER_SIZE = 4096;
	char buffer[BUFFER_SIZE];

	std::ifstream myFile;
	std::string currentLine;

	myFile.open(in_path);
	if(myFile.is_open() && !myFile.bad())
	{
		std::smatch regexMatch;

		std::string regexNumberPattern = "-?\\d+.\\d+\\s*";

		std::regex vertexRegex("v\\s*" + regexNumberPattern + regexNumberPattern + regexNumberPattern);// "-?\\d+.\\d+\\s*-?\\d+.\\d+\\s*-?\\d+.\\d+");
		std::regex uvRegex("vt\\s*" + regexNumberPattern + regexNumberPattern);
		std::regex normalRegex("vn\\s*" + regexNumberPattern + regexNumberPattern + regexNumberPattern);
		int count = 0;
		while(myFile.getline(buffer, BUFFER_SIZE))
		{
			currentLine = buffer;

			std::sregex_iterator regVertexIter = std::sregex_iterator(currentLine.begin(), currentLine.end(), vertexRegex);
			std::sregex_iterator regUVIter = std::sregex_iterator(currentLine.begin(), currentLine.end(), uvRegex);
			std::sregex_iterator regNormalIter = std::sregex_iterator(currentLine.begin(), currentLine.end(), normalRegex);

			/*for(;regVertexIter != std::sregex_iterator(); ++regVertexIter)
			{
				//std::cout << regVertexIter->str() << std::endl;
				std::cout << "hey: " << count << std::endl;

				count++;
			}
			if(count > 0)
				break;

			//std::cout << std::endl;
			for(;regUVIter != std::sregex_iterator(); ++regUVIter)
			{
				//std::cout << regUVIter->str() << std::endl;
			}

			//std::cout << std::endl;
			for(;regNormalIter != std::sregex_iterator(); ++regNormalIter)
			{
				//std::cout << regNormalIter->str() << std::endl;
			}*/
		}
		
		return true;
	}
	else
	{
		std::cout << "File " << in_path << " does not exist!" << std::endl;
		return false;
	}

	
}