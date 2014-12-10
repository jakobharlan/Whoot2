#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <String>
#include "GL/glew.h"


static class ShaderLoader {
public:
  static GLuint createProgramFromStrings(std::string const& v, std::string const& f);
  static GLuint createProgramFromFiles(std::string const& v, std::string const& f);
    
private:
  static GLuint loadShader(GLenum type, std::string const& s);

};


#endif 
//SHADER_LOADER_H