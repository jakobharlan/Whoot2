#ifndef PARTICLE_PASS_H
#define PARTICLE_PASS_H

#include "GL/glew.h"

#include <vector>

#include "shader.h"

struct Position{
	float x;
	float y;
	float z;
};

class ParticlePass{

public:
  ParticlePass();
  ParticlePass(unsigned numParticles);

  void draw();

private:
  void init_data();

  unsigned m_num_particles;

  std::vector<Position> m_particle_positions;

  // flip value to switch between buffers
  bool m_flip;

  // two vbo`s and vao`s, alternating for feedback and for drawing
  GLuint m_vao_a;
  GLuint m_vao_b;

  GLuint m_vbo_a;
  GLuint m_vbo_b;

  GLuint m_simulation_shader_program;
  Shader m_render_shader;
};


#endif 
//PARTICLE_PASS_H