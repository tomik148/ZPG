#version 330
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location=0) in vec3 vertexPos;

out vec3 colour;

void main () {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vertexPos, 1.0);
	colour = vertexPos;
}