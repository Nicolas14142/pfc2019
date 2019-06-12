#include "Particle.h"

class Space 
{
public:
	int n_particles;
	float target;
	float target_error; 
	int Pbest = 0;
	float gbest_value;
	float gbest_position[2];
	Particle particles[12];
	float fitness_candidate, best_fitness_candidate;
	float range = 50;
	float new_velocity[2];
	float velocity_max = 1;
	float c1 = 0.1, c2 = 4, att = 5, rep = 1, W = 1;
	float dest[2];
	int entrei = 0;
	float* positions[24];

	Space(float, float, int);
	void print_particles();
	float fitness(Particle);
	void set_pbest();
	int set_gbest();
	void move_particles(int);
	void move_dest();
	float random();
	void init();
	void potential_field(Particle,bool);
	void set_target(float, float);
	void make_pointer();
	void set_const(float, float, float, float, float);
	float* PSO(float, float, float, float, int, int, float, float, float, float, float);

};


