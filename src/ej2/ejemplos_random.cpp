#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

int main() {
	srand(time(NULL));
	ofstream testFile;
	int maximoXY;
	unsigned int pueblosMin;
	unsigned int pueblosMax;
	unsigned int salteaDeA;
	unsigned int centrales;
	cout << "inserte coordenada maxima de pueblos:";
	cin >> maximoXY;
	cout << "inserte la cantidad de pueblos minima:";
	cin>> pueblosMin;
	cout << "inserte la cantidad de pueblos maxima:"; 
	cin>> pueblosMax;
	cout << "inserte de a cuantos pueblos saltear:"; 
	cin>> salteaDeA;
	testFile.open("tests_random");
	

	testFile << "-mediciones" << endl;
	for (unsigned int pueblos = pueblosMin; pueblos <= pueblosMax; pueblos=pueblos+salteaDeA) {
		centrales = (rand() % pueblos)+1;
		//Creo una instancia del problema
		testFile << pueblos << " " << centrales << endl;
		for (unsigned int i = 0; i < pueblos; i++) {
		
			int signoX = (rand() % 2);
			if (signoX == 0){
	
				signoX = -1;
			}
			int x = (rand() % maximoXY) * signoX ;
			
			int signoY = (rand() % 2)-1;
			if (signoY == 0){
				signoY = -1;
			}
			int y = (rand() % maximoXY) * signoY ;
			testFile << x << " " << y << endl;
			
		}

	}
	
	testFile.close();
}
	
