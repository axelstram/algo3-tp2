using namespace std;
#include "tipos.h"
#include "matrix.h"
#include <string>
#include <cstring>
#include <fstream>

int main();
void resolver(Nat nPueblos, Nat kCentrales, list<Coordenada>& pueblos, bool mostrarResultado);

bool ordenPares (const pair<Arista,double>& par1, const pair<Arista,double>& par2);
list<Nat> generarEstaciones(list<pair<Arista,double> > bosqueMinimo, Nat nPueblos);
void mostrar(Nat kCentrales, Nat cantidadTuberias, list<Nat> estaciones, list<pair<Arista,double> >& bosqueMinimo);
timespec diff(timespec start, timespec end);
