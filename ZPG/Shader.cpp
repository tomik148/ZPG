#include "Shader.h"


Shader::Shader()
{
	/*
	vertex_shader =
		"#version 330\n"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"layout(location=0) in vec3 vp;"
		"out vec3 colour;"
		"void main () {"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"     colour = vp;"
		"}";
	fragment_shader =
		"#version 330\n"
		"in vec3 colour;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (colour,1);"
		"}";
*/
	std::ifstream myfile("../ZPG/vertex.vert");
	std::stringstream buffer;
	buffer << myfile.rdbuf();
	std::string temp = buffer.str();
	vertex_shader = &temp[0u];
	myfile.close();

	std::ifstream myfile2("../ZPG/fragment.frag");
	std::stringstream buffer2;
	buffer2 << myfile2.rdbuf();
	std::string temp2 = buffer2.str();
	fragment_shader = &temp2[0u];
	myfile2.close();

	//create and compile shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	/*
	modelMatrixID = glGetUniformLocation(shaderProgram, "modelMatrix");
	viewMatrixID = glGetUniformLocation(shaderProgram, "viewMatrix");
	projectionMatrixID = glGetUniformLocation(shaderProgram, "projectionMatrix");
	*/
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

}

void Shader::SetAsProgram()
{
	glUseProgram(shaderProgram);
}

GLint Shader::AddMatrix(glm::mat4 matrix, const char * nameInShader)
{
	GLint ret = glGetUniformLocation(shaderProgram, nameInShader);
	glUniformMatrix4fv(ret, 1, GL_FALSE, glm::value_ptr(matrix));
	return ret;
}


Shader::~Shader()
{
}
