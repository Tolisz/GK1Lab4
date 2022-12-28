#version 330 core
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

out vec4 FragColor;

void main()
{
    //FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    FragColor = texture(texture_diffuse1, TexCoords) + texture(texture_specular1, TexCoords);
}