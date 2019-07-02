// ParticleSwarmOptimization.cpp : Define as funções exportadas para o aplicativo DLL.
//

#include "Particle.h"
#include "Space.h"
#include <iostream>
#include <cstdlib>
#include <time.h>       /* time */
//#include <stdio.h>      /* printf, scanf, puts, NULL */
#include "PSO_dll.h"

DLLEXPORT void ParticleSwarmOptimization1(double positions[24], double vel[24], int n_particles) {
	float target = 10;
	float c1 = 0.1;
	float c2 = 4;
	float att = 5;
	float rep = 1;
	float W = 1;

	double *lastBestPositions = (double*) malloc(sizeof(double) * 3 * n_particles);
	double *velocities = (double*) malloc(sizeof(double) * 2 * n_particles);
	double debug[20] = {0};

	for (int j=0; j< 3*n_particles; j++) {
		lastBestPositions[j] = std::numeric_limits<double>::infinity();
	}
	
	ParticleSwarmOptimization(
			positions[0], positions[1],
			target,
			n_particles,
			c1,
			c2,
			att,
			rep,
			W,
			&(positions[2]),
			lastBestPositions,
			velocities,
			debug);
}


DLLEXPORT void ParticleSwarmOptimization(float dest_x, float dest_y, float target, int n_particles, float c1, float c2, float att, float rep, float W, double positions[24], double last_pbest[36], double vel[24], double debug[20]) {

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

	for (int i = 0; i < search_space.n_particles; i++) {
		//set last_pbest
		search_space.particles[i].pbest_value = last_pbest[3 * i];
		search_space.particles[i].pbest_position[0] = last_pbest[3 * i + 1];
		search_space.particles[i].pbest_position[1] = last_pbest[3 * i + 2];

		//set last_velocities
		search_space.particles[i].velocity[0] = vel[2 * i];
		search_space.particles[i].velocity[1] = vel[2 * i + 1];

		//set positions
		search_space.particles[i].position[0] = positions[2 * i];
		search_space.particles[i].position[1] = positions[2 * i + 1];
	}

	//execute the algorithm
	search_space.PSO(dest_x, dest_y, n_particles, last_pbest, positions, c1, c2, att, rep, W);

	debug[3] = search_space.gbest_value;
	debug[4] = search_space.gbest_position[0];
	debug[5] = search_space.gbest_position[1];
	debug[6] = search_space.c1;
	debug[7] = search_space.Pbest;

	for (int i = 0; i < search_space.n_particles; i++) {
		//return pbest
		last_pbest[3 * i] = search_space.particles[i].pbest_value;
		last_pbest[3 * i + 1] = search_space.particles[i].pbest_position[0];
		last_pbest[3 * i + 2] = search_space.particles[i].pbest_position[1];

		//return new positions
		positions[2 * i] = search_space.particles[i].position[0];
		positions[2 * i + 1] = search_space.particles[i].position[1];
	
		//return new velocities
		vel[2 * i] = search_space.particles[i].velocity[0];
		vel[2 * i + 1] = search_space.particles[i].velocity[1];
	}
}

DLLEXPORT void PsoTest() {
	std::cout << "Teste de chamada da biblioteca" <<  std::endl;
}

DLLEXPORT void PsoTest2(double positions[], int nrParticles ) {
	std::cout << "Teste de chamada da biblioteca" << std::endl;
	std::cout << "\t Nr Particles: " << nrParticles << std::endl;
	std::cout << "\t positions: [" << positions[0];
	for (int i=1; i<nrParticles; i++){
		std::cout << ", " << positions[i];
	}
	std::cout << "]" << std::endl;
}