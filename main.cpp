#include "cryptohash.h"
#include <iostream>

using namespace std;
int main() {
	/*
	cout << execute(500000, 300000, 200000) << " collisions" << endl;
	cout << execute(400000, 300000, 300000) << " collisions" << endl;
	cout << execute(600000, 200000, 200000) << " collisions" << endl;
	cout << execute(800000, 100000, 100000) << " collisions" << endl;
	*/

	srand(time(NULL) );

	/*
	
	teste.conf[0] = 30000 ;
	teste.conf[1] = 50000 ;
	teste.conf[2] = 20000 ;
	teste.conf[3] = execute(teste.conf[0],teste.conf[1],teste.conf[0]);
	
	cout << resultado.conf[3] << endl;*/

	Configuration max;
	int flag = 0;	
	for(size_t i = 0; i < 24; i++ ){
		Configuration teste, resultado;
		int generated;
		teste.conf[2] = SIZE_M;
		for(size_t j = 0; j < 2; j++){ 
			generated = random()+(10000*j);
			teste.conf[j] = (generated % teste.conf[2]) + 1;
			teste.conf[2] -= teste.conf[j];
		}
		

		cout <<teste.conf[0] << endl;
		cout <<teste.conf[1] << endl;
		cout <<teste.conf[2] << endl;
		// clog << pop[i][0] << '\t' << pop[i][1] << '\t' << pop[i][2] << endl ;

		teste.conf[3] = execute(teste.conf[0], teste.conf[1], teste.conf[2]);
		cout << teste.conf[3] << endl;
		hill_climbing(teste,resultado);

		if (flag == 0){
			max = teste;
			flag++;	
		}

		if(resultado.conf[3] > max.conf[3])
			max = resultado;
	}	

		cout << "MAXIMO" << endl;
		printf_conf(max);
	return 0;
}






