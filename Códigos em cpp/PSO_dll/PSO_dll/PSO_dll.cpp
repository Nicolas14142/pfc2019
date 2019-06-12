// ParticleSwarmOptimization.cpp : Define as funções exportadas para o aplicativo DLL.
//

#include "stdafx.h"
#include "Particle.h"
#include "Space.h"
#include <cstdlib>
#include <time.h>       /* time */
//#include <stdio.h>      /* printf, scanf, puts, NULL */

__declspec(dllexport) void ParticleSwarmOptimization(float dest_x, float dest_y, float target, int n_particles, float c1, float c2, float att, float rep, float W, double positions[24], double last_pbest[36], double vel[24], double debug[20]){

	using namespace std;
	srand(time(NULL));
	
	Space search_space;
	search_space.set_target(target);
	search_space.set_n_particles(n_particles);
	search_space.set_dest(dest_x, dest_y); //seta o destino do grupo
	search_space.set_id();
	search_space.set_const(c1, c2, att, rep, W); //seta os pesos do PSO

	debug[0] = search_space.dest[0];
	debug[1] = search_space.dest[1];
	debug[2] = search_space.n_particles;
	debug[3] = search_space.gbest_position[0];
	debug[4] = search_space.gbest_position[1];
	debug[5] = search_space.gbest_value;

	//set last_pbest
	for (int i = 0; i < search_space.n_particles; i++) {

		search_space.particles[i].pbest_value = last_pbest[3 * i];
		search_space.particles[i].pbest_position[0] = last_pbest[3 * i + 1];
		search_space.particles[i].pbest_position[1] = last_pbest[3 * i + 2];
	}

	//set last_velocities
	for (int i = 0; i < search_space.n_particles; i++) {

		search_space.particles[i].velocity[0] = vel[2 * i];
		search_space.particles[i].velocity[1] = vel[2 * i + 1];
	}

	//set positions
	for (int i = 0; i < search_space.n_particles; i++) {

		search_space.particles[i].position[0] = positions[2 * i];
		search_space.particles[i].position[1] = positions[2 * i + 1];
	}

	//execute the algorithm
	search_space.PSO(dest_x, dest_y, n_particles, last_pbest, positions, c1, c2, att, rep, W);

	debug[6] = search_space.c1;
	debug[7] = search_space.Pbest;

	//return pbest
	for (int i = 0; i < search_space.n_particles; i++) {

		last_pbest[3 * i] = search_space.particles[i].pbest_value;
		last_pbest[3 * i + 1] = search_space.particles[i].pbest_position[0];
		last_pbest[3 * i + 2] = search_space.particles[i].pbest_position[1];
	}

	//return new positions
	for (int i = 0; i < search_space.n_particles; i++) {

		positions[2 * i] = search_space.particles[i].position[0];
		positions[2 * i + 1] = search_space.particles[i].position[1];
	}
	
	//return new velocities
	for (int i = 0; i < search_space.n_particles; i++) {

		vel[2 * i] = search_space.particles[i].velocity[0];
		vel[2 * i + 1] = search_space.particles[i].velocity[1];
	}
}

