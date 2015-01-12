#ifndef SPRITEBATCHER_SIMENGINE
#define SPRITEBATCHER_SIMENGINE

#include "../OpenGL/GLIncludes.h"
#include "../Rendering/SpriteComponent.h"

namespace
{
    const GLfloat mSpriteVertices[] =
    {	// position					//texcoords
        -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,
        
        0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f
    };
};

class SpriteBatcher
{
public:
	~SpriteBatcher();
    
private:
    GLuint mSpriteVao;
    GLuint mSpriteVbo;
};

#endif