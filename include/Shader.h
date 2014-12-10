#ifndef SHADER_H
#define SHADER_H

#include <String>
#include "GL/glew.h"


class Shader {
public:
  Shader();
  void createProgramFromStrings(std::string const& v, std::string const& f);
  void createProgramFromFiles(std::string const& v, std::string const& f);
  void makeActive();
  GLuint getUniformLocation(std::string const& name);
    
private:
  GLuint loadShader(GLenum type, std::string const& s);

  GLuint m_shaderProgramm;
};


#endif 
//SHADER_H
