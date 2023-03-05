#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform vec4 ourColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	//FragColor = vertexColor;
	//FragColor = vertexColor; // 片元着色器固定输出
	//FragColor = texture(ourTexture, TexCoord);
	//FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}