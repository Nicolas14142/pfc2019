#ifndef __Particle
#define __Particle

class Particle 
{
public:
	float position[2];
	float pbest_position[2];
	float pbest_value;
	float velocity[2];
	float range = 5;
	int id;
	
	Particle ();
	void set_position(float, float);
	void str();
	void move();
	float random();
	float velocity_mod();
	void limit_velocity(float speed_limit);

	Particle & operator=(const Particle & p);
	Particle & operator+(const Particle & p) const;
};
#endif