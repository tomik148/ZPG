#version 330
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 Normal;

uniform vec3 lightPosition = vec3(0,0,0);
uniform vec3 cameraPosition;

out vec3 colour;
out vec3 normal;
out vec3 lightPos;
out vec3 cameraPos;
out vec3 worldPos;

void main () {

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vertexPos, 1.0);
	worldPos = ( modelMatrix * vec4 (vertexPos, 1.0)).xyz;
	colour = abs(Normal);
	normal = (modelMatrix * vec4 (Normal, 1.0)).xyz;
	lightPos = normalize(lightPosition);
	cameraPos = cameraPosition;
}