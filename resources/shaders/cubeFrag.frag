#version 330 core
out vec4 fragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D Emisive;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

// camera pos
uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main() {
// ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

// diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
    
// specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));
        
// emisive
    vec3 emisive = vec3(texture(material.Emisive, texCoords));

    vec3 result = ambient + diffuse + specular + emisive;
    fragColor = vec4(result, 1.0);
};