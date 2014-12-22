#include "Shader.h"

#include <iostream>
#include <fstream>

#include "ShaderLoader.h"

// Public: 
Shader::Shader():
m_shader_program(0)
{}

Shader::Shader(std::string const& v, std::string const& f)
{
  m_shader_program = ShaderLoader::createProgramFromFiles(v,f);  
}

void Shader::makeActive() const
{
  glUseProgram(m_shader_program);
}

GLuint Shader::getUniformLocation(std::string const& name) const
{
  return glGetUniformLocation(m_shader_program, name.data());
}

void Shader::set_shader_program(GLuint shader_program)
{
	m_shader_program = shader_program;
}