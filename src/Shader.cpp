#include <Shader.h>

#include <iostream>

// Public: 
Shader::Shader():
m_shaderProgramm(0)
{}


void Shader::createProgramFromStrings(std::string const& v, std::string const& f){
	GLuint id = glCreateProgram();

	GLuint vsHandle = loadShader(GL_VERTEX_SHADER, v);
	GLuint fsHandle = loadShader(GL_FRAGMENT_SHADER, f);
	glAttachShader(id, vsHandle);
	glAttachShader(id, fsHandle);
	// schedule for deletion
	glDeleteShader(vsHandle);
	glDeleteShader(fsHandle);

	glLinkProgram(id);
	GLint successful;

	glGetProgramiv(id, GL_LINK_STATUS, &successful);
	if (!successful) {
	  int length;
	  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
	  std::string info(length, ' ');

	  glGetProgramInfoLog(id, length, &length, &info[0]);
	  
	  std::cout << "Linking of Shaders failed: " << std::endl;
	  std::cout << info << std::endl;
	}
  std::cout << "Creating of Shader succesful" << std::endl;
	m_shaderProgramm = id;
}

void Shader::createProgramFromFiles(std::string const& v, std::string const& f){
	return;
}

void Shader::makeActive()
{
	glUseProgram(m_shaderProgramm);
}

GLuint Shader::getUniformLocation(std::string const& name)
{
	return glGetUniformLocation(m_shaderProgramm, name.data());
}

// Private:
GLuint Shader::loadShader(GLenum type, std::string const& s){
	GLuint id = glCreateShader(type);
	const char* source = s.c_str();
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	GLint successful;
	glGetShaderiv(id, GL_COMPILE_STATUS, &successful);

	if (!successful) {
	  int length;
	  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	  std::string info(length, ' ');

	  glGetShaderInfoLog(id, length, &length, &info[0]);
	  std::cout << "Compiling of Shader failed: " << std::endl;
	  std::cout << info << std::endl;
	}
	return id;
}