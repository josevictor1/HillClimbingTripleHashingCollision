#include "collision.h"

int main() {
	/*
	cout << execute(500000, 300000, 200000) << " collisions" << endl;
	cout << execute(400000, 300000, 300000) << " collisions" << endl;
	cout << execute(600000, 200000, 200000) << " collisions" << endl;
	cout << execute(800000, 100000, 100000) << " collisions" << endl;
	*/
	Configuration teste, resultado;
	teste.conf[0] = 30000 ;
	teste.conf[1] = 50000 ;
	teste.conf[2] = 20000 ;
	teste.conf[3] = execute(teste.conf[0],teste.conf[1],teste.conf[0]);
	hill_climbing(teste,resultado);
	cout << resultado.conf[3] << endl;
	return 0;
}






