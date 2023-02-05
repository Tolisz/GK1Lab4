#version 330 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;


struct DayLight
{
    vec3 direction;
      
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DayLight day_light;
uniform vec3 viewPos;

vec3 CalcDayLight(DayLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);

    FragColor = vec4(CalcDayLight(day_light, normalize(Normal), viewDir), 1.0f);
}

vec3 CalcDayLight(DayLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 200);

    vec3 ambient  = light.ambient * (vec3(texture(texture_diffuse1, TexCoords)) + vec3(texture(texture_specular1, TexCoords)));
    vec3 diffuse  = light.diffuse * diff * (vec3(texture(texture_diffuse1, TexCoords)) + vec3(texture(texture_specular1, TexCoords)));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

    return ambient + diffuse + specular;
}

