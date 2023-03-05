#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform vec4 ourColor;
uniform sampler2D ourTexture;//使用默认的纹理单元

void main() {
	//FragColor = vertexColor;
	//FragColor = vertexColor; // 片元着色器固定输出
	//FragColor = texture(ourTexture, TexCoord);
	FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor);
}