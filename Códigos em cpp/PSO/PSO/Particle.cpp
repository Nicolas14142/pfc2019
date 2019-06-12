#include "Particle.h"
#include <cstdlib>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <iostream>

Particle::Particle() {

	position[0] = random();
	position[1] = random();
	pbest_position[0] = abs(random());
	pbest_position[1] = abs(random());
	pbest_value = 10000000;
	velocity[0] = 0;
	velocity[1] = 0;
}

void Particle::set_position(float x, float y) {
	position[0] = x;
	position[1] = y;
}

void Particle::str() {

	std::cout << "Position: " << position[0] <<", "<< position[1] << " Pbest: " << pbest_position[0] << ", " << pbest_position[1] << "\n";
}

void Particle::move() {

	this->position[0] = position[0] + velocity[0];
	this->position[1] = position[1] + velocity[1];
	
}

float Particle::velocity_mod() {

	float vel = velocity[0] * velocity[0] + velocity[1] * velocity[1];
	vel = sqrt(vel);
	
	return vel;
}

void Particle::limit_velocity(float speed_limit) {

	float mod = this->velocity_mod();
	if (mod <= speed_limit) {
		//do nothing
	}
	else {
		this->velocity[0] = (speed_limit / mod)*velocity[0];
		this->velocity[1] = (speed_limit / mod)*velocity[1];
	}
}

float Particle::random() {

	//srand(time(NULL));
	//gera aleatório de -1 a 1
	float random = ((float)rand() / (RAND_MAX)) * 2 - 1;
	random = random * range;
	return random;
}

// Definição da sobrecarga do operador =
Particle & Particle::operator=(const Particle & p)
{
	if (this == &p) return *this; // opcional, evita auto cópia
	this->position[0] = p.position[0];
	this->position[1] = p.position[1];
	return *this;
}

// Definição da sobrecarga do operador binário +
Particle & Particle::operator+(const Particle & p) const
{
	Particle * pp = new Particle;
	pp->position[0] = this->position[0] + p.position[0];
	pp->position[1] = this->position[1] + p.position[1];
	return *pp;
}