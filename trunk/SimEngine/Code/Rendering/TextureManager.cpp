//
//  TextureManager.cpp
//  OpenGL Attempt1
//
//  Created by Simon McDonnell on 13/08/2014.
//  Copyright (c) 2014 ___SimonMcDonnell___. All rights reserved.
//

#include "../Rendering/TextureManager.h"
#include <iostream>

TextureManager::TextureManager()
{
    
}

TextureManager::~TextureManager()
{
    DumpTextureCache();
}

TextureData TextureManager::GetTexture(const GLchar* path)
{
    // Do this but in a non horrible way, tie it to the state somehow? Maybe bring back the Scene and tie it to that instead
    
    // Search texture cache for image
	for(uint32_t i = 0; i < mTextureCache.size(); ++i)
	{
		if(mTextureCache[i].mName == std::string(path))
		{
			return mTextureCache[i];
		}
	}
    
    // If this is a new image
    return LoadTexture(path);
}

TextureData TextureManager::LoadTexture(const GLchar* path)
{
	GLuint* texture = NULL;
	glGenTextures(1, texture);
	GLint width = 0, height = 0;
    
	unsigned char* image = NULL;
    
	const std::string imagePath = "../OpenGL Attempt1/Assets/Images/";
    
	std::string amendedPath(path);
	amendedPath = imagePath + amendedPath;
    
	glBindTexture(GL_TEXTURE_2D, *texture);
	image = SOIL_load_image(amendedPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	if(image == NULL)
	{
        std::cout << "Image " << path << " is null!" << std::endl;
		std::cout << "SOIL error: " << SOIL_last_result() << std::endl;
	}
	SOIL_free_image_data(image);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	TextureData newTexData(path, texture, width, height);
	mTextureCache.push_back(newTexData);
    
	return newTexData;
}

void TextureManager::DumpTextureCache()
{
    for(uint32_t i = 0; i < mTextureCache.size(); ++i)
    {
        glDeleteTextures(1, mTextureCache[i].mTextureID);
    }
    
    mTextureCache.clear();
}
