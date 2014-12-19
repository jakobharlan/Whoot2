#include "FullScreenPass.h" 


// public:
FullScreenPass::FullScreenPass():
m_quat_vao(0),
m_quat_vbo(0),
m_shader("../Whoot2/shader/basic.vert", "../Whoot2/shader/basic.frag")
{
  init_quad();
  m_time_uniform_location = m_shader.getUniformLocation("time");
}


void FullScreenPass::draw()
{
  // float time = static_cast<float>(glfwGetTime());
  glUniform1f(m_time_uniform_location, 0.0);

  m_shader.makeActive();

  glBindVertexArray(m_quat_vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);

  return;
}


void FullScreenPass::init_quad()
{
  // Data
  float vertices[] = {-0.98f,-0.98f,0.0f,1.0f,
            -0.98f,0.98f,0.0f,1.0f,
            0.98f,0.98f,0.0f,1.0f,
            -0.98f,-0.98f,0.0f,1.0f,
            0.98f,0.98f,0.0f,1.0f,
            0.98f,-0.98f,0.0f,1.0f};

  // VertexArrayObject 
  glGenVertexArrays(1,&m_quat_vao);
  glBindVertexArray(m_quat_vao);

  // VertexBufferObject
  glGenBuffers(1, &m_quat_vbo);
  glBindBuffer(GL_ARRAY_BUFFER,m_quat_vbo);
  glBufferData(GL_ARRAY_BUFFER,6*4* sizeof(float),vertices,GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,0);

  // unbind
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// private: