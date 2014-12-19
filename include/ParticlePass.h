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

  GLuint m_vao;
  GLuint m_vbo;

  Shader m_shader;
};


#endif 
//PARTICLE_PASS_H