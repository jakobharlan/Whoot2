#include <Shader.h>

#include <iostream>
#include <fstream>

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
    
    std::cout << "Linking of Shaders failed " << std::endl;
    std::cout << info << std::endl;
    m_shaderProgramm = 0;
  }else{
    std::cout << "Creating of Shader succesful" << std::endl;
    m_shaderProgramm = id;
  }
}

void Shader::createProgramFromFiles(std::string const& v, std::string const& f)
{
  std::ifstream in_v(v, std::ios::in | std::ios::binary);
  std::ifstream in_f(f, std::ios::in | std::ios::binary);
  std::string vertex_contents;
  std::string fragment_contents;
  
  if(in_v)
  {
    in_v.seekg(0, std::ios::end);
    vertex_contents.resize(in_v.tellg());
    in_v.seekg(0, std::ios::beg);
    in_v.read(&vertex_contents[0], vertex_contents.size());
    in_v.close();
  }else{
    std::cout << "failed to open file: " << v << std::endl;
  }
  if(in_f)
  {
    in_f.seekg(0, std::ios::end);
    fragment_contents.resize(in_f.tellg());
    in_f.seekg(0, std::ios::beg);
    in_f.read(&fragment_contents[0], fragment_contents.size());
    in_f.close();
  }else{
    std::cout << "failed to open file: " << f << std::endl;
  }

  createProgramFromStrings(vertex_contents, fragment_contents);

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