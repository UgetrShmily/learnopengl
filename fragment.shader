#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform vec4 ourColor;
uniform sampler2D ourTexture;//ʹ��Ĭ�ϵ�����Ԫ

void main() {
	//FragColor = vertexColor;
	//FragColor = vertexColor; // ƬԪ��ɫ���̶����
	//FragColor = texture(ourTexture, TexCoord);
	FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor);
}