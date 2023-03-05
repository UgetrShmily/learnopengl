#version 330 core
layout(location = 0) in vec3 aPos; // λ��
layout(location = 1) in vec3 aColor; // ��ɫ
layout(location = 2) in vec2 aTexCoord; // ����

out vec4 vertexColor;
out vec2 TexCoord;

void main() {
	gl_Position = vec4(aPos, 1.0);
	vertexColor = vec4(aColor, 1.0);
	TexCoord = aTexCoord;
}