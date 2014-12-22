#include <ShaderLoader.h>

#include <iostream>
#include <fstream>


GLuint ShaderLoader::createProgramFromStrings(std::string const& v, std::string const& f){
  GLuint id = glCreateProgram();

  GLuint vsHandle = loadShader(GL_VERTEX_SHADER, v);
  GLuint fsHandle = loadShader(GL_FRAGMENT_SHADER, f);
  glAttachShader(id, vsHandle);
  glAttachShader(id, fsHandle);

  glLinkProgram(id);
  GLint successful;

  // schedule for deletion
  glDeleteShader(vsHandle);
  glDeleteShader(fsHandle);

  glGetProgramiv(id, GL_LINK_STATUS, &successful);
  if (!successful) {
    int length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
    std::string info(length, ' ');

    glGetProgramInfoLog(id, length, &length, &info[0]);
    
    std::cout << "Linking of Shaders failed " << std::endl;
    std::cout << info << std::endl;
    return 0;
  }else{
    std::cout << "Creating of Shader succesful" << std::endl;
    return id;
  }
}

GLuint ShaderLoader::createProgramFromFiles(std::string const& v_path, std::string const& f_path)
{
  std::string vertex_contents = load_file(v_path);
  std::string fragment_contents = load_file(f_path);
  
  return createProgramFromStrings(vertex_contents, fragment_contents);
}

std::string const ShaderLoader::load_file(std::string const& filepath)
{
  std::ifstream in(filepath, std::ios::in | std::ios::binary);
  std::string file_contents;

  if(in)
  {
    in.seekg(0, std::ios::end);
    file_contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&file_contents[0], file_contents.size());
    in.close();
  }else{
    std::cout << "failed to open file: " << filepath << std::endl;
  }

  return file_contents;
}

GLuint ShaderLoader::loadShader(GLenum type, std::string const& s){
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