#if !defined(unix) && !defined(__unix__) && !defined(__unix)
	#include "stdafx.h"
#else
	#include <cstdlib>
	#include <cmath>
#endif
#include "Particle.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <iostream>
#include <time.h>

Particle::Particle() {
#if defined(unix) || defined(__unix__) || defined(__unix)
	position[0] = random();
	position[1] = random();
	pbest_position[0] = abs(random());
	pbest_position[1] = abs(random());
	pbest_value = 10000000;
	velocity[0] = 0;
	velocity[1] = 0;
#endif
}

void Particle::set_position(double x, double y) {
	position[0] = x;
	position[1] = y;
}

void Particle::str() {

	std::cout << "Position: " << position[0] << ", " << position[1] << " Pbest: " << pbest_position[0] << ", " << pbest_position[1] << "\n";
}

void Particle::move() {

	this->position[0] = position[0] + velocity[0];
	this->position[1] = position[1] + velocity[1];

}

double Particle::velocity_mod() {

	double vel = velocity[0] * velocity[0] + velocity[1] * velocity[1];
	vel = sqrt(vel);

	return vel;
}

void Particle::limit_velocity(double speed_limit) {

	double mod = this->velocity_mod();
	if (mod <= speed_limit) {
		//do nothing
	}
	else {
		this->velocity[0] = (speed_limit / mod)*(this->velocity[0]);
		this->velocity[1] = (speed_limit / mod)*(this->velocity[1]);
	}
}

double Particle::random() {

	//srand(time(NULL));
	//gera aleatório de -1 a 1
	double random = ((double)rand() / (RAND_MAX)) * 2 - 1;
	random = random * range;
	return random;
}

/*

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
*/