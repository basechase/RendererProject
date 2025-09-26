#version 430 core

in vec2 vertUV;

out vec4 vertColor;

layout (location = 5) uniform sampler2D albedo;

void main()
{
    // RED and GREEN to illustrate that UVs are working
    ///vertColor = vec4(vertUV.x, vertUV.y, 0, 1);
    vertColor = texture(albedo, vertUV);
}