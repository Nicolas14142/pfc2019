#include "Space.h"
#include <cstdlib>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <iostream>


Space::Space(float target, float target_error, int n_particles) {

	this->target = target;
	this->target_error = target_error;
	this->n_particles = n_particles;
	this->gbest_position[0] = random()*range;
	this->gbest_position[1] = random()*range;
	this->dest[0] = -25;//random()*range;
	this->dest[1] = -25;//random()*range;
	this->gbest_value = 10000000;
}



void Space::print_particles() {
	for (int i = 0; i < n_particles; i++) {

		particles[i].id = i;
		particles[i].str();
		std::cout << "Dest: " << dest[0] << ", " << dest[1] << "\n";
		std::cout << random() << "\n";
	}
}

float Space::fitness(Particle p) {

	return abs(100 - pow((p.position[1] - dest[1]),2) - pow((p.position[0] - dest[0]),2));
}

void Space::set_pbest() {
	for (int i = 0; i < n_particles; i++) {

		fitness_candidate = this->fitness(particles[i]);
		if (particles[i].pbest_value > fitness_candidate) {
			this->particles[i].pbest_value = fitness_candidate;
			this->particles[i].pbest_position[0] = particles[i].position[0];
			this->particles[i].pbest_position[1] = particles[i].position[1];
		}
	}
}

int Space::set_gbest() {
	gbest_value = 100000;
	for (int i = 0; i < n_particles; i++) {
		
		best_fitness_candidate = fitness(particles[i]);
		if (gbest_value > best_fitness_candidate) {
			this->gbest_value = best_fitness_candidate;
			this->gbest_position[0] = this->particles[i].position[0];
			this->gbest_position[1] = this->particles[i].position[1];
			this->Pbest = i;
			entrei = 1 - entrei;
		}
	}
	return Pbest;
}

void Space::move_particles(int Pb) {
	for (int i = 0; i < n_particles; i++) {

		//this->new_velocity[0] = (W*particles[i].velocity[0]) + (c1*abs(random()))*(particles[i].pbest_position[0] - particles[i].position[0]) + (c2*abs(random()))*(this->gbest_position[0] - particles[i].position[0]);
		//this->new_velocity[1] = (W*particles[i].velocity[1]) + (c1*abs(random()))*(particles[i].pbest_position[1] - particles[i].position[1]) + (c2*abs(random()))*(this->gbest_position[1] - particles[i].position[1]);

		//particle velocity.max limited

		if (false) {

			potential_field(particles[i], true);
		}
		else {
			this->new_velocity[0] = (W*particles[i].velocity[0]) + (c1*abs(random()))*(particles[i].pbest_position[0] - particles[i].position[0]) + (c2*abs(random()))*(this->gbest_position[0] - particles[i].position[0]);
			this->new_velocity[1] = (W*particles[i].velocity[1]) + (c1*abs(random()))*(particles[i].pbest_position[1] - particles[i].position[1]) + (c2*abs(random()))*(this->gbest_position[1] - particles[i].position[1]);
			potential_field(particles[i], false);
		}
		particles[i].velocity[0] = new_velocity[0];
		particles[i].velocity[1] = new_velocity[1];
		particles[i].limit_velocity(velocity_max);
		particles[i].move();
	}
}

void Space::move_dest() {
	//velocidade do objetivo 2x maior q o da partícula
	this->dest[0] = dest[0] + velocity_max/3;
	this->dest[1] = dest[1] + velocity_max/3;
}

void Space::potential_field(Particle p, bool attractive) {

	float u[2] = { 0,0 };
	//Force of Attraction
	if (attractive == true) {
		u[0] = att * (this->dest[0] - p.position[0]);
		u[1] = att * (this->dest[1] - p.position[1]);
	}
	//Force of Repulsion

	for (int i = 0; i < n_particles; i++) {

		if (p.id != particles[i].id) {
			u[0] = u[0] - rep*1/((particles[i].position[0] - p.position[0]));
			u[1] = u[1] - rep*1/((particles[i].position[1] - p.position[1]));
		} 
	}
	
	new_velocity[0] = new_velocity[0] + u[0];
	new_velocity[1] = new_velocity[1] + u[1];
}
	
void Space::init() {
	for (int i = 0; i < n_particles; i++) {

		//particles


	}
}


float Space::random() {

	// srand(time(NULL));
	//gera aleatório de -1 a 1
	float random = ((float)rand() / (RAND_MAX))*2- 1;
	//random = random * range
	return random;
}

void Space::make_pointer() {
	for (int i = 0; i < n_particles; i++) {
		*positions[2*i] = particles[i].position[0];
		*positions[2*i+1] = particles[i].position[1];
	}
}

void Space::set_target(float x, float y) {
	dest[0] = x;
	dest[1] = y;
}

void Space::set_const(float c1, float c2, float att, float rep, float W) {
	this->c1 = c1;
	this->c2 = c2;
	this->att = att;
	this->rep = rep;
	this->W = W;

}

float* Space::PSO(float target_x, float target_y, float target, float target_error, int n_particles, int last_Pb, float c1, float c2, float att, float rep, float W) {
	//return particle next position
	//Space search_space(target, target_error, n_particles);
	srand(time(NULL));
	set_const(c1,c2,att,rep,W);
	set_target(target_x,target_y);
	//search_space.Pbest = last_Pb;
	set_pbest();
	int Pb = set_gbest();

	if (abs(gbest_value - target) <= target_error) {
		return nullptr;
	}
	//write(search_space, i);
	move_particles(Pb);
	move_dest();
	//std::cout << i << "\n";//<<"\t"<<" "<<Pb<<" "<<search_space.entrei<<"\t"<< search_space.fitness(search_space.particles[Pb])<<" "<< search_space.gbest_value <<"\t"<< search_space.particles[Pb].position[0]<<" "<< search_space.gbest_position[0]<<"\n";
	make_pointer();
	return positions[0];
}

