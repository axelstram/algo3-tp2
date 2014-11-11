#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//Genera listas de cartas para n = 1... 1000, y para cada n, el rango de valores de las cartas se mueve entre -n y +n

int main() {

	srand(time(NULL));
	ofstream tests;
	tests.open("tests_aleatorios");
	int MAX_CARTAS = 1000;

	for (int maximoDeCartas = 1; maximoDeCartas <= MAX_CARTAS; maximoDeCartas+=25) {
		
		tests << maximoDeCartas << " ";

		for (int cantCartas = 1; cantCartas <= maximoDeCartas; cantCartas++) {

			int nroRandom = 2*(rand() % maximoDeCartas + 1);
			int carta = nroRandom - maximoDeCartas;
			
			tests << carta << " ";

		}

		tests << endl;

	}

	tests << 0;
	tests.close();

}
