#include "Particle.h"
#include "Space.h"
#include <cstdlib>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>      // std::setprecision

void write(Space &search_space, int j);

int main() {

	float target = 0;
	float target_error = 0.0001;
	int n_iterations = 500;
	int n_particles = 10;
	srand(time(NULL));

	Space search_space(target, target_error, n_particles);
	search_space.print_particles();
	//Particle test;
	//test.str();
	std::cout << "Destino" << search_space.dest[0] << "\n";
	int i = 0, Pb = 0;
	for (i = 0; i < n_iterations;i++) {

		search_space.set_pbest();
		Pb = search_space.set_gbest();

		if (abs(search_space.gbest_value - search_space.target) <= search_space.target_error) {
			break;
		}
		write(search_space,i);
		search_space.move_particles(Pb);
		search_space.move_dest();
		std::cout << i<<"\n"<<"\t"<<" "<<Pb<<" "<<search_space.entrei<<"\t"<< search_space.fitness(search_space.particles[Pb])<<" "<< search_space.gbest_value <<"\t"<< search_space.particles[Pb].position[0]<<" "<< search_space.gbest_position[0]<<"\n";
		
	}
	std::cout << "The best solution is: " << search_space.gbest_position[0] << ", " << search_space.gbest_position[1]<<"\n";
	std::cout << "The real best solution is: " << search_space.particles[Pb].position[0] << ", " << search_space.particles[Pb].position[1];

	std::cout << " in n_iterations: " << i <<"\n\n";

#if !defined(unix) && !defined(__unix__) && !defined(__unix)
	system("pause");
#else
  system("read -p 'Press Enter to continue...' var");
#endif 
	
	return 0;
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
