#include <Shader.h>

#include <iostream>
#include <fstream>

#include "ShaderLoader.h"

// Public: 
Shader::Shader():
m_shaderProgramm(0)
{}

Shader::Shader(std::string const& v, std::string const& f)
{
  m_shaderProgramm = ShaderLoader::createProgramFromFiles(v,f);  
}

void Shader::makeActive() const
{
  glUseProgram(m_shaderProgramm);
}

GLuint Shader::getUniformLocation(std::string const& name) const
{
  return glGetUniformLocation(m_shaderProgramm, name.data());
}

