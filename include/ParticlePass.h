#ifndef PARTICLE_PASS_H
#define PARTICLE_PASS_H

#include "GL/glew.h"


class ParticlePass {

public:
  ParticlePass();
  ParticlePass(unsigned numParticles);

private:
  unsigned m_numParticles;
};


#endif 
//PARTICLE_PASS_H