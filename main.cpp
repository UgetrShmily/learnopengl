#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Data
float vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};
unsigned int indices[] = {
	// ע��������0��ʼ! 
	// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
	// �����������±��������ϳɾ���

	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

float texCoords[] = {
	0.0f, 0.0f, // ���½�
	1.0f, 0.0f, // ���½�
	0.5f, 1.0f // ����
};

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	// ��ʼ��
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "����GLFW����ʧ�ܣ�" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD��ʼ��ʧ�ܣ�" << std::endl;
		return -1;
	}

	// ��ʾ����
	glViewport(0, 0, 800, 600);

	// ע��ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ���ݴ���
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);// ����λ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // ��ɫ
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // ����
	glEnableVertexAttribArray(2);

	// ��ɫ��
	Shader shader("vertex.shader", "fragment.shader");
	glBindVertexArray(VAO);
	glUseProgram(shader.ID);

	// ����
	int width, height, nrChannels;
	unsigned int texture1, texture2;
	unsigned char* data;



	glGenTextures(1, &texture1);
	//glActiveTexture(GL_TEXTURE0); // �ڰ�����֮ǰ�ȼ�������Ԫ��PS��Ĭ�ϼ���0������Ԫ���Ҳ�����Ĭ��ʹ�ø�����Ԫ����ʡ�ԣ�
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Ϊ��ǰ���������û��ƹ���(����)��ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ͼƬ���ݶ�ȡʧ��" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1); // ����1������Ԫ uniform sampler2D texture2;
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Ϊ��ǰ���������û��ƹ���(����)��ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true); // ��תy��
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ͼƬ���ݶ�ȡʧ��" << std::endl;
	}
	stbi_image_free(data);
	// �����������������Ӧ������Ԫ
	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��Ⱦ
		/*glBindVertexArray(VAO);
		glUseProgram(shader.ID);*/

		float timeValue = glfwGetTime();
		float greenValue = ((sin(timeValue) + 1) / 2.0f);
		glUniform4f(glGetUniformLocation(shader.ID, "ourColor"), 0.0f, greenValue, 0.0f, 1.0f);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// �����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}