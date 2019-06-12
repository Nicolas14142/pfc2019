// stdafx.h: arquivo de inclusão para arquivos de inclusão padrão do sistema,
// ou arquivos de inclusão específicos a um projeto que são usados frequentemente, mas
// são modificados raramente
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Excluir itens raramente utilizados dos cabeçalhos do Windows
// Arquivos de Cabeçalho do Windows
#include <windows.h>



struct input
{
	
};

__declspec(dllexport) void ParticleSwarmOptimization(float dest_x, float dest_y, float target, int n_particles, float c1, float c2, float att, float rep, float W, double positions[24], double last_pbest[36], double vel[24], double debug[20]);



// referenciar os cabeçalhos adicionais de que seu programa precisa aqui

#include "Particle.h"
#include "Space.h"
#include "stdafx.h"