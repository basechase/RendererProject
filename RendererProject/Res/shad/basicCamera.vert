#version 430 core

// Vertex Attributes
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 normal;


// Uniforms
layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

layout (location = 3) uniform float time;
layout (location = 4) uniform float displacement = 5;



out vec2 vertUV;
out vec3 vNormal;
out vec4 vPos;


void main()
{

	// EXPORTS to FRAGMENT SHADER
	vPos = position;
	vNormal = mat3(transpose(inverse(model))) * normal.xyz;
	vertUV = uv;
	vertUV.x += sin(time);

	// VERTEX SHADER LOGIC POSITION
	vec4 myPosition = position;
	myPosition.y += sin(time) * displacement;

	// transform object from ...
	// - OBJECT to WORLD  (model)
	// - WORLD  to CAMERA (view)
	// - CAMERA to CLIP   (proj)
	gl_Position = proj * view * model * myPosition;
}