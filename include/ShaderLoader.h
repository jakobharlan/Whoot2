#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <String>
#include "GL/glew.h"


class ShaderLoader {
public:
  static GLuint createProgramFromStrings(std::string const& v, std::string const& f);
  static GLuint createProgramFromFiles(std::string const& v_path, std::string const& f_path);
  static std::string const load_file(std::string const& filepath);
  static GLuint loadShader(GLenum type, std::string const& s);
    
private:

};


#endif 
//SHADER_LOADER_H