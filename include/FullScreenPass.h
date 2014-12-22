#ifndef FULL_SCREEN_PASS_H
#define FULL_SCREEN_PASS_H

#include "GL/glew.h"

#include "shader.h"

class FullScreenPass {

public:
  FullScreenPass();

  void draw() const;

private:
  void init_quad();

  GLuint m_vao;
  GLuint m_vbo;
  GLuint m_time_uniform_location;

  Shader m_shader;
};


#endif 
//FULL_SCREEN_PASS_H