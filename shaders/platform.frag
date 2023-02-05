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

struct PointLight {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

struct FlashLight
{
    vec3 position;  
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform FlashLight latarka;

uniform PointLight point_light;

uniform vec3 Normal;
uniform vec3 viewPos;

vec3 CalcDayLight(DayLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcFlashLight(FlashLight light, vec3 normal, vec3 viewDir);



void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);

    FragColor = vec4(
        CalcDayLight(day_light, normalize(Normal), viewDir) +
        CalcPointLight(point_light, normalize(Normal), viewDir) + 
        CalcFlashLight(latarka, normalize(Normal), viewDir), 1.0f);
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

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;  
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 200);
    vec3 specular = light.specular * spec * material.specular;  
    
    // attenuation
    float dist = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    return ambient + diffuse + specular;
}

vec3 CalcFlashLight(FlashLight light, vec3 normal, vec3 viewDir)
{
    // ambient
    vec3 ambient = light.ambient *  material.ambient;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;  
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 200);
    vec3 specular = light.specular * spec * material.specular;  
    
    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    return ambient + diffuse + specular;
}