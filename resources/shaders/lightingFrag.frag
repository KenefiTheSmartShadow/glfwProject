#version 330 core

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform float ambientStrength;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main() {
// ambient
    vec3 ambiet = ambientStrength * lightColor;
// diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambiet + diffuse) * objectColor;
    fragColor = vec4(result, 1.0);
};