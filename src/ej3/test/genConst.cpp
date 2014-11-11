#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void generarInstancia(ostream& testFile, const unsigned int n, const unsigned int potenciaExtraMaxima, const unsigned int potenciaMaxima);

int main(int argc, char** argv) {
	/* Primer parámetro: nombre de archivo donde va a escribir los tests.
	   Segundo parámetro: número de filas y columnas.
	   Tercer parámetro: potencia de cada casillero.
	   Cuarto parámetro: potencia extra.
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
	
	//srand(time(NULL));
	ofstream testFile;
	unsigned int n = atoi(argv[2]);
	unsigned int potenciaMaxima = atoi(argv[3]);
	unsigned int potenciaExtraMaxima = atoi(argv[4]);
	int instancias = atoi(argv[5]);
	testFile.open(argv[1]);
	
	for (int i = 0; i < instancias; i++) {
		generarInstancia(testFile, n, potenciaExtraMaxima, potenciaMaxima);
	}
	testFile << 0;
	testFile.close();
}

void generarInstancia(ostream& testFile, const unsigned int n, const unsigned int potenciaExtra, const unsigned int potencia) {
	testFile << n << " ";
	int posOrigenFila = 1;
	int posOrigenColumna = 1;
	int posDestinoFila = n;
	int posDestinoColumna = n;
	testFile << posOrigenFila << " ";
	testFile << posOrigenColumna << " ";
	testFile << posDestinoFila << " ";
	testFile << posDestinoColumna << " ";
	testFile << potenciaExtra << " ";
	testFile << endl;
	for (unsigned int i = 1; i <= n; i++) {
		for (unsigned int p = 1; p <= n; p++) {
			testFile << potencia << " ";
		}
		testFile << endl;
	}
}

