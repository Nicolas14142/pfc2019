
#ifndef __PSO_H
#define __PSO_H

#if !defined(unix) && !defined(__unix__) && !defined(__unix)
	#include "stdafx.h"
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT
#endif

void ParticleSwarmOptimization(float dest_x, float dest_y, float target, int n_particles, float c1, float c2, float att, float rep, float W, double positions[24], double last_pbest[36], double vel[24], double debug[20]);

#endif