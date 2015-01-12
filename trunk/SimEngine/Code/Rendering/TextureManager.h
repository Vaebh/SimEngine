//
//  TextureManager.h
//  OpenGL Attempt1
//
//  Created by Simon McDonnell on 07/08/2014.
//  Copyright (c) 2014 ___SimonMcDonnell___. All rights reserved.
//

#ifndef TEXTUREMANAGER_SIMEGINE
#define TEXTUREMANAGER_SIMEGINE

#include "../Foundation/Foundation.h"
#include "../OpenGL/GLIncludes.h"

#include <vector>
#include <string>

struct TextureData
{
	TextureData(const std::string& inName = "", GLuint* inTexID = NULL, uint32_t inWidth = 0, uint32_t inHeight = 0) :
    mName(inName),
    mTextureID(inTexID),
    mWidth(inWidth),
    mHeight(inHeight)
    {}
    
	std::string mName;
	GLuint* mTextureID;
	uint32_t mWidth;
	uint32_t mHeight;
};

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    
    TextureData GetTexture(const GLchar* path);
    TextureData LoadTexture(const GLchar* path);
    
    void DumpTextureCache();
    
private:
    std::vector<TextureData> mTextureCache;
};

#endif
