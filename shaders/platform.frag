#version 330 core
out vec4 FragColor;

in vec3 FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

struct DayLight
{
    vec3 direction;
      
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DayLight day_light;

uniform vec3 Normal;
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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;

    return ambient + diffuse + specular;
}