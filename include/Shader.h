#ifndef SHADER_H
#define SHADER_H

#include <String>
#include "GL/glew.h"


class Shader {
public:
  Shader();
  Shader(std::string const& v, std::string const& f);
  void makeActive() const;
  GLuint getUniformLocation(std::string const& name) const;
    
  void set_shader_program(GLuint shader_program);

private:
  GLuint m_shader_program;
};


#endif 
//SHADER_H
