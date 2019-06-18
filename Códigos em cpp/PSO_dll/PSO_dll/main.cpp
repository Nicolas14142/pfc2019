#include "Particle.h"
#include "Space.h"
#include <cstdlib>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>      // std::setprecision
#include <limits>
#include "PSO_dll.h"

double dest[2] = {0, 0};
double positions[] = {1.0448, -2.62078, 3.92514, -1.71163, -2.63939, -1.51814, -4.96704, -0.834529, 2.07358, -2.72515, 2.54875, -0.731986, 0.872982, 3.13623, 1.20991, -3.54701, 3.92209, 3.27113, 3.13807, -2.32444};
double infinity = std::numeric_limits<double>::infinity();
double *lastBestPositions;
double *velocities;
double debug[20] = {0};

void write1(int, double*, double[2], int);
void write(Space &search_space, int j);

#define iterationMaxDistance 2000
#define incrementStep 1

#define iterationIsNotOver ( (dest[0] > iterationMaxDistance) ? 0 : 1 )
#define increment(x) (x[0]+=incrementStep, x[1]+=incrementStep)

int main() {

	float target = 10;
	int n_particles = 5;
	float c1 = 0.1;
	float c2 = 4;
	float att = 5;
	float rep = 1;
	float W = 1;

	lastBestPositions = (double*) malloc(sizeof(double) * 3 * n_particles);
	velocities = (double*) malloc(sizeof(double) * 2 * n_particles);
	for (int j=0; j<36; j++) lastBestPositions[j] = 1000000;
	for (int j=0; j<36; j++) std::cout << lastBestPositions[j] << " ";
	std::cout << std::endl;
  
	srand(time(NULL));

	int i = 0;
	while (iterationIsNotOver) { // for (i = 0; i < n_iterations; i++) {
		std::cout << "i = " << i << std::endl;
		ParticleSwarmOptimization(dest[0], dest[1], target, n_particles, c1, c2, att, rep, W, positions, lastBestPositions, velocities, debug);

		std::cout << "Best Positions" << std::endl;
		for (int j=0; j< 3 * n_particles; j++) std::cout << lastBestPositions[j] << " ";
		std::cout << std::endl;

		std::cout << "Velocities: ";
		for (int j=0; j< 2 * n_particles; j++) std::cout << velocities[j] << " ";
		std::cout << std::endl;

		std::cout << "GBest: " << debug[3] << "\t" << debug[4] << "\t" << debug[5] << "\t" << std::endl;

		write1(n_particles, positions, dest, i++);
		increment(dest);
	}

	for (i = 0; i < n_particles ; i++) {
		std::cout << positions[i*2] << ", " << positions[i*2 + 1] << ", ";
	}
	std::cout << std::endl;

#if !defined(unix) && !defined(__unix__) && !defined(__unix)
	system("pause");
#else
  system("read -p 'Press Enter to continue...' var");
#endif 
	
	return 0;
}

void write1(int nrParticles, double positions[], double destPosition[2] , int j)
{
	using namespace std;
	fstream fout;
	
	if(j==0) fout.open("enxame.csv", ofstream::out | ofstream::trunc);
	else fout.open("enxame.csv", ios::out | ios::app);

	int i;
	for (i = 0; i < nrParticles ; i++) {
		fout << positions[i*2] << ", " << positions[i*2 + 1] << ", ";
		// cout << positions[i*2] << ", " << positions[i*2 + 1] << ", ";
	}
	
	fout << destPosition[0] << "," << destPosition[1] << "\n";
	// cout << destPosition[0] << "," << destPosition[1] << "\n";
}

void write(Space &search_space, int j)
{
	using namespace std;
	// file pointer 
	fstream fout;
	// opens an existing csv file or creates a new file. 
	
	if(j==0) fout.open("enxame.csv", ofstream::out | ofstream::trunc);
	else fout.open("enxame.csv", ios::out | ios::app);

	int i;

	for (i = 0; i < search_space.n_particles ; i++) {

		// Insert the data to file 
		fout << search_space.particles[i].position[0] << ", "
			<< search_space.particles[i].position[1] << ", ";
	}
	
	fout << search_space.dest[0] <<","
	<< search_space.dest[1]<<"\n";

	//fout<< "\n";
}

