#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

// #define GLFW_DLL
// #define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "ParticlePass.h"
#include "FullScreenPass.h"

GLFWwindow* wd;           /* window desciptor/handle */
GLint width  = 1024;
GLint height = 800;         /* initial window width and height */
int fbwidth, fbheight;    /* framebuffer width and height (Retina display) */

/* function where all the actual drawing happens */
void draw(GLuint vao, GLuint time_location)
{
  float time = static_cast<float>(glfwGetTime());
  glUniform1f(time_location, time);
  /* color buffer must be cleared each time */
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);


  /* GLFW is ALWAYS double buffered; will call glFlush() */
  glfwSwapBuffers(wd);

  return;
}

/* Callback functions for GLFW */

void init_data()
{
  return;
}

/* Called when framebuffer is resized, e.g., when window is resized
 * NOT called automatically when window is first created.
 * Called by GLFW BEFORE reshape().
*/
void fbreshape(GLFWwindow *wd, int w, int h)
{
  /* save new framebuffer dimensions */
  fbwidth = w;
  fbheight = h;

  /* do an orthographic parallel projection with the view volume
   set to first quadrant, fixed to the initial window dimension */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (float)fbwidth, 0.0, (float)fbheight, -1.f, 1.f);

  /* Tell OpenGL to use the whole window for drawing.
   Note that we don't resize the view volume, so
   the viewport will show the whole view volume 
   shrunk/stretched to fit the current view port. */
  glViewport(0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

  init_data();
  
  return;
}

/* Called when window is resized.
 * NOT called automatically when window is first created.
 * Called by GLFW AFTER fbreshape().
*/
void reshape(GLFWwindow *wd, int w, int h)
{
  /* save new screen dimensions */
  width = w;
  height = h;

  return;
}

/* Called when window is closed,
   also when 'q' or ESC is hit. */
void quit(GLFWwindow *wd)
{
  glfwDestroyWindow(wd);
  glfwTerminate();
  exit(0);
}

void kbd(GLFWwindow* wd, int key, int scancode, int action, int mods)
{
  if (action == GLFW_RELEASE) { // function is called first on GLFW_PRESS.
  return;
  }
  
  switch (key) {
  case GLFW_KEY_ESCAPE:
    quit(wd);
    break;
  case GLFW_KEY_SPACE:
    std::cout << "Space" << std::endl;
    break;
  default:
    break;
  }
  
  return;
}

void charhd(GLFWwindow* wd, unsigned int key)
{
  switch (key) {
  case 'q':
    quit(wd);
    break;
  default:
    break;
  }

  return;
}

void err(int errcode, const char* desc)
{
  std::cout << errcode << desc << std::endl;

  return;
}

void initgl()
{ 
  /* clear color buffer to white */
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  
  return;
}

int main(int argc, char *argv[])
{
  glfwSetErrorCallback(err);
  if (!glfwInit()) {
  exit(1);
  }

  /* create the window and its associated OpenGL context */
  wd = glfwCreateWindow(width, height, "Whoot 2",
            NULL, NULL);
  if (!wd) {
  glfwTerminate();
  exit(1);
  }
  /* make the window's context the current context */
  glfwMakeContextCurrent(wd);
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
  std::cout << "glewInit failed!" << std::endl;
  std::cout << glewGetErrorString(err) << std::endl;
  }
  glfwGetFramebufferSize(wd, &fbwidth, &fbheight);

  /* shape view port */
  fbreshape(wd, fbwidth, fbheight);
  
  /* --- register callbacks with GLFW --- */

  /* register function to handle window resizes */
  glfwSetFramebufferSizeCallback(wd, fbreshape);
  glfwSetWindowSizeCallback(wd, reshape);

  /* register function to handle window close */
  glfwSetWindowCloseCallback(wd, quit);

  /* register function to handle keyboard input */
  glfwSetKeyCallback(wd, kbd);      // general keyboard input
  glfwSetCharCallback(wd, charhd);  // simpler specific character handling


  initgl();

  FullScreenPass myFSP = FullScreenPass();
  ParticlePass myPP = ParticlePass(10000);
  
  do {
    /* color buffer must be cleared each time */
    glClear(GL_COLOR_BUFFER_BIT);

    myFSP.draw();
    
    /* GLFW is ALWAYS double buffered; will call glFlush() */
    glfwSwapBuffers(wd);
    
    glfwPollEvents();
  } while (!glfwWindowShouldClose(wd));

  exit(0);
}

