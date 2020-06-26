#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform CameraBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(binding = 2) uniform TransformBufferObject {
    mat4 transform[1024];
} transforms;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColour;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 normal;
layout(location = 3) out vec3 fragPos;

void main() {
    gl_Position = ubo.proj * ubo.view * transforms.transform[gl_InstanceIndex] * vec4(inPosition, 1.0);
    fragColour = inColour;
    fragTexCoord = inTexCoord;
    normal = mat3(transpose(inverse(transforms.transform[gl_InstanceIndex]))) * inNormal;  
    fragPos = vec3(transforms.transform[gl_InstanceIndex] * vec4(inPosition, 1.0));
}