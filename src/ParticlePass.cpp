#include "ParticlePass.h" 

#include <stdlib.h>
#include <iostream>

// public:
ParticlePass::ParticlePass():
m_num_particles(0)
{}

ParticlePass::ParticlePass(unsigned numParticles):
m_num_particles(numParticles),
m_vao(0),
m_vbo(0),
m_shader("../Whoot2/shader/particle.vert", "../Whoot2/shader/particle.frag")
{
	init_data();
}

void ParticlePass::draw()
{
  m_shader.makeActive();

  glBindVertexArray(m_vao);
  glDrawArrays(GL_POINTS, 0, m_num_particles);
  glBindVertexArray(0);

  return;
}

void ParticlePass::init_data()
{
	// Data
	for (unsigned i = 0; i < m_num_particles; ++i)
	{
		Position tmp;
		tmp.x = ( (float(rand()) / RAND_MAX) - 0.5) * 2.0;
		tmp.y = ( (float(rand()) / RAND_MAX) - 0.5) * 2.0;
		tmp.z = 0.0;

		m_particle_positions.push_back(tmp);
	}

	// VertexArrayObject 
	glGenVertexArrays(1,&m_vao);
	glBindVertexArray(m_vao);

	// VertexBufferObject
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
	glBufferData(GL_ARRAY_BUFFER,m_num_particles*3* sizeof(float),&m_particle_positions[0],GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// private: