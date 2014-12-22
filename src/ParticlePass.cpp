#include "ParticlePass.h" 

#include <stdlib.h>
#include <utility>
#include <iostream>
#include <String>

#include "ShaderLoader.h"

// public:
ParticlePass::ParticlePass():
m_num_particles(0)
{}

ParticlePass::ParticlePass(unsigned numParticles):
m_num_particles(numParticles),
m_flip(true),
m_vao_a(0),
m_vao_b(0),
m_vbo_a(0),
m_vbo_b(0),
m_simulation_shader_program(0),
m_render_shader("../Whoot2/shader/particle.vert", "../Whoot2/shader/particle.frag")
{
  //set up simulation shader program
  std::string shader_contents = ShaderLoader::load_file("../Whoot2/shader/particle_simulation.vert");
  GLuint simulation_vertex_shader = ShaderLoader::loadShader(GL_VERTEX_SHADER, shader_contents);
  
  m_simulation_shader_program = glCreateProgram();
  glAttachShader(m_simulation_shader_program, simulation_vertex_shader);

  const GLchar* feedbackVaryings[] = { "out_position" };
  glTransformFeedbackVaryings(m_simulation_shader_program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
  
  glLinkProgram(m_simulation_shader_program);

  init_data();
}

void ParticlePass::draw()
{
  GLuint old_vao(0);
  GLuint new_vao(0);
  GLuint new_vbo(0); 

  if (m_flip)
  {
    old_vao = m_vao_a;
    new_vao = m_vao_b;
    new_vbo = m_vbo_b;
  }else{
    old_vao = m_vao_b;
    new_vao = m_vao_a;
    new_vbo = m_vbo_a;
  }

  // bind buffers for simulation
  glBindVertexArray(old_vao);

  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, new_vbo);
  
  // particle siumulation
  glUseProgram(m_simulation_shader_program);
  glEnable(GL_RASTERIZER_DISCARD);
  glBeginTransformFeedback(GL_POINTS);
  glDrawArrays(GL_POINTS, 0, m_num_particles);
  glEndTransformFeedback();
  glFlush();
  glDisable(GL_RASTERIZER_DISCARD);
  // glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, new_vbo);


  // bind buffers for rendering
  glBindVertexArray(new_vao);

  // particle rendering
  m_render_shader.makeActive();
  glDrawArrays(GL_POINTS, 0, m_num_particles);
  glBindVertexArray(0);

  // flip the flip to change between frames
  m_flip = !m_flip;

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
  glGenVertexArrays(1,&m_vao_a);
  glBindVertexArray(m_vao_a);

  // VertexBufferObject
  glGenBuffers(1, &m_vbo_a);
  glBindBuffer(GL_ARRAY_BUFFER,m_vbo_a);
  glBufferData(GL_ARRAY_BUFFER,m_num_particles*3* sizeof(float),&m_particle_positions[0],GL_DYNAMIC_COPY);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
  
  // unbind
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  
  // VertexArrayObject 
  glGenVertexArrays(1,&m_vao_b);
  glBindVertexArray(m_vao_b);
  
  // VertexBufferObject
  glGenBuffers(1, &m_vbo_b);
  glBindBuffer(GL_ARRAY_BUFFER,m_vbo_b);
  glBufferData(GL_ARRAY_BUFFER,m_num_particles*3* sizeof(float), nullptr ,GL_DYNAMIC_COPY);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

  // unbind
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// private: