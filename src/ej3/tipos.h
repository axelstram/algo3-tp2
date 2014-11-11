#include <vector>
#include <utility>
#include <list>

using namespace std;

#ifndef NAT
#define NAT
typedef unsigned int Nat;
#endif

#ifndef COORDENADA
#define COORDENADA
typedef pair<int, int> Coordenada;
#endif

#ifndef MATRIZ
#define MATRIZ
typedef vector<vector<Nat> > Matriz;
#endif

#ifndef COORDENADA_Y_POTENCIA
#define COORDENADA_Y_POTENCIA
typedef pair<Coordenada, Nat> CoordenadaYPotencia;
#endif
