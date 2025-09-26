#version 430 core

// Vertex Attributes
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;

// Uniforms
layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

layout (location = 3) uniform float time;
//layout (location = 4) uniform float displacement = 5;

out vec2 vertUV;

void main()
{
	// EXPORTS to FRAGMENT SHADER
	vertUV = uv;
	vertUV.x += sin(time);

	// VERTEX SHADER LOGIC POSITION
	vec4 myPosition = position;
	//myPosition.y += sin(time) * displacement;

	// transform object from ...
	// - OBJECT to WORLD  (model)
	// - WORLD  to CAMERA (view)
	// - CAMERA to CLIP   (proj)
	gl_Position = proj * view * model * myPosition;
}