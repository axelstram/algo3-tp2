#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void generarInstancia(ostream& testFile, const unsigned int n, const unsigned int potenciaExtraMaxima, const unsigned int potenciaMaxima);

int main(int argc, char** argv) {
	/* Primer parámetro: nombre de archivo donde va a escribir los tests.
	   Segundo parámetro: número de filas y columnas.
	   Tercer parámetro: potencia máxima de cada casillero.
	   Cuarto parámetro: potencia extra máxima.
	   Quinto parámetro: número de instancias generadas.
	*/
	if (argc > 6) {
		cerr << "Demasiados parametros." << endl;
		exit(EXIT_FAILURE);
	}
	if (argc < 6) {
		cerr << "Pocos parametros." << endl;
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	ofstream testFile;
	unsigned int n = atoi(argv[2]);
	unsigned int potenciaMaxima = atoi(argv[3]);
	unsigned int potenciaExtraMaxima = atoi(argv[4]);
	int instancias = atoi(argv[5]);
	testFile.open(argv[1]);
	
	for (int i = 0; i < instancias; i++) {
		generarInstancia(testFile, n, potenciaExtraMaxima, potenciaMaxima);
	}
	/*
	testFile << n << " ";
	int posOrigenFila = (rand() % n)+1;
	int posOrigenColumna = (rand() % n)+1;
	int posDestinoFila = (rand() % n)+1;
	int posDestinoColumna = (rand() % n)+1;
	testFile << posOrigenFila << " ";
	testFile << posOrigenColumna << " ";
	testFile << posDestinoFila << " ";
	testFile << posDestinoColumna << " ";
	int potenciaExtra = (rand() % (potenciaExtraMaxima+1));
	testFile << potenciaExtra << " ";
	testFile << endl;
	for (unsigned int i = 1; i <= n; i++) {
		for (unsigned int p = 1; p <= n; p++) {
			int nroRandom = (rand() % potenciaMaxima)+1;
			testFile << nroRandom << " ";
		}
		testFile << endl;
	}
	*/
	testFile << 0;
	testFile.close();
}

void generarInstancia(ostream& testFile, const unsigned int n, const unsigned int potenciaExtraMaxima, const unsigned int potenciaMaxima) {
	testFile << n << " ";
	int posOrigenFila = (rand() % n)+1;
	int posOrigenColumna = (rand() % n)+1;
	int posDestinoFila = (rand() % n)+1;
	int posDestinoColumna = (rand() % n)+1;
	testFile << posOrigenFila << " ";
	testFile << posOrigenColumna << " ";
	testFile << posDestinoFila << " ";
	testFile << posDestinoColumna << " ";
	int potenciaExtra = (rand() % (potenciaExtraMaxima+1));
	testFile << potenciaExtra << " ";
	testFile << endl;
	for (unsigned int i = 1; i <= n; i++) {
		for (unsigned int p = 1; p <= n; p++) {
			int nroRandom = (rand() % potenciaMaxima)+1;
			testFile << nroRandom << " ";
		}
		testFile << endl;
	}
}

