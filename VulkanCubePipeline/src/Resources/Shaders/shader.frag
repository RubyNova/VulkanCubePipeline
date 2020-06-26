#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 3) uniform lightPosData {
    vec3 lightPos;
};
layout(location = 0) in vec3 fragColour;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 fragPos;

layout(location = 0) out vec4 outColour;

void main() {
    //ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * fragColour;
    vec4 textureSample = texture(texSampler, fragTexCoord);
    //outColour = vec4(ambient, 1) * textureSample;

    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1, 1, 1);

    //specular
    float specularStrength = 10;
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * vec3(1, 1, 1); 

    outColour = vec4((ambient + diffuse + specular), 1) * textureSample;
}