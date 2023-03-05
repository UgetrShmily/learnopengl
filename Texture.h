#pragma once
#include <glad/glad.h>
class Texture
{
public:
	unsigned int ID;
	/**激活纹理单元并创建纹理*/
	Texture(const char* filename, GLenum texture);
};

