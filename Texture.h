#pragma once
#include <glad/glad.h>
class Texture
{
public:
	unsigned int ID;
	/**��������Ԫ����������*/
	Texture(const char* filename, GLenum texture);
};

