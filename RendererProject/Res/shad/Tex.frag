#version 430 core


layout (location = 5) uniform sampler2D albedo;
layout (location = 6) uniform vec3 ambientLightColor;
layout (location = 7) uniform vec3 lightDir;
layout (location = 8) uniform vec3 lightColor;

in vec4 vPos;
in vec2 vertUV;
in vec3 vNormal;

out vec4 vertColor;


void main()
{
    // RED and GREEN to illustrate that UVs are working
    ///vertColor = vec4(vertUV.x, vertUV.y, 0, 1);
   
   float d = max(0, dot(vNormal, -lightDir));
   
   vec3 diffuse = d * lightColor;

    vec4 base = texture(albedo, vertUV);

    vertColor.xyz = base.xyz * (ambientLightColor + diffuse);
    vertColor.a = base.a;

    //vertColor = texture(albedo, vertUV);
}