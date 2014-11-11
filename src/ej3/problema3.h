#include "tipos.h"
#include "matrix.h"
#include "latablita.h"
#include "caminomin.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>



int main(int argc, char** argv);
void MedirTiempo(string& nombreDeArchivo);
void ResolverNormalmente();
void CargarCasilleros(const Nat n, Matriz& casilleros);
list<CoordenadaYPotencia> Resolver(const Matrix& laMatrix, const Nat potenciaExtra, const Coordenada origen, const Coordenada destino);
void ObtenerYMarcarPuntosAdyacentes(list<CoordenadaYPotencia>& lista, LaTablita& tabla, const Matrix& laMatrix, const Coordenada posDeSalto, const Coordenada destinoAbsoluto, const Nat potenciaDisponible);
void MarcarYAgregar(const Matrix& laMatrix, list<CoordenadaYPotencia>& lista, const Coordenada posOrigen, const Coordenada posDestino, LaTablita& tabla, const Nat potenciaDisponible, const Nat potenciaExtra);
void Imprimir(list<CoordenadaYPotencia>& solucion);
timespec diff(timespec start, timespec end);
