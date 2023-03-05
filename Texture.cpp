#include "Texture.h"
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>

Texture::Texture(const char* filename, GLenum texture)
{
	int width, height, nrChannels;
	unsigned char* data;
	glGenTextures(1, &ID);
	glActiveTexture(texture); // 在绑定纹理之前先激活纹理单元（PS：默认激活0号纹理单元，且采样器默认使用该纹理单元，可省略）
	glBindTexture(GL_TEXTURE_2D, ID);
	// 为当前绑定纹理设置环绕过滤(采样)方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//放大
	/**
	* 多级渐远纹理
	GL_NEAREST_MIPMAP_NEAREST	使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
	GL_LINEAR_MIPMAP_NEAREST	使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
	GL_NEAREST_MIPMAP_LINEAR	在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
	GL_LINEAR_MIPMAP_LINEAR	在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//缩小（多级渐远）
	data = stbi_load(filename, &width, &height, &nrChannels, 0);


	if (data) {
		if (nrChannels > 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "图片数据读取失败" << std::endl;
	}
	stbi_image_free(data);

}
