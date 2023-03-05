#include "Texture.h"
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>

Texture::Texture(const char* filename, GLenum texture)
{
	int width, height, nrChannels;
	unsigned char* data;
	glGenTextures(1, &ID);
	glActiveTexture(texture); // �ڰ�����֮ǰ�ȼ�������Ԫ��PS��Ĭ�ϼ���0������Ԫ���Ҳ�����Ĭ��ʹ�ø�����Ԫ����ʡ�ԣ�
	glBindTexture(GL_TEXTURE_2D, ID);
	// Ϊ��ǰ���������û��ƹ���(����)��ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//�Ŵ�
	/**
	* �༶��Զ����
	GL_NEAREST_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ������ƥ�����ش�С����ʹ���ڽ���ֵ�����������
	GL_LINEAR_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ�����𣬲�ʹ�����Բ�ֵ���в���
	GL_NEAREST_MIPMAP_LINEAR	��������ƥ�����ش�С�Ķ༶��Զ����֮��������Բ�ֵ��ʹ���ڽ���ֵ���в���
	GL_LINEAR_MIPMAP_LINEAR	�������ڽ��Ķ༶��Զ����֮��ʹ�����Բ�ֵ����ʹ�����Բ�ֵ���в���
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//��С���༶��Զ��
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
		std::cout << "ͼƬ���ݶ�ȡʧ��" << std::endl;
	}
	stbi_image_free(data);

}
