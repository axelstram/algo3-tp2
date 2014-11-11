#include <vector>
#include <utility>
#include <list>
#include <tuple>
#include <iostream>

using namespace std;

#ifndef NAT
#define NAT
typedef unsigned int Nat;
#endif

#ifndef COORDENADA
#define COORDENADA
typedef pair<double, double> Coordenada;
#endif

#ifndef ARISTA
#define ARISTA
typedef pair<Nat, Nat> Arista;
#endif

#ifndef MATRIZ
#define MATRIZ
typedef vector<vector<pair<double,Nat>> > Matriz;
#endif
