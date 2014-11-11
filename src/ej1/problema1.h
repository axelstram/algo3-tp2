#include "jugador.h"
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cassert>


typedef pair<int, Jugada> JugadaOptima; // < beneficio a mi favor, jugada que debo hacer >
typedef vector<vector<JugadaOptima> > MatrizOpt;



void CargarCartas(list<int>& cartasEnLaMesa);
void ImprimirSolucion(list<int>& cartasEnLaMesa, Jugador& jugador1, Jugador& jugador2, int cantTurnos);
void RealizarJugadaOptimaEntre(int& inicioSubsecuenciaDeCartas, int& finSubsecuenciaDeCartas, list<int>& cartasEnLaMesa, Jugador& jugador, MatrizOpt& matrizJugadasOptimas);
void GenerarTodasLasJugadasOptimas(list<int>& cartasEnLaMesa, MatrizOpt& matrizJugadasOptimas);
Jugada ObtenerMejorJugadaEntre(int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, MatrizOpt& matrizJugadasOptimas);
void ActualizarPuntajeJugador(list<int>& cartasEnLaMesa, Jugador& jugador, Jugada jugada);
void ResolverYTomarMedicionesDe(const char* nombreArchivoTest);
void ResolverNormalmente();
int Robanumeros(list<int> cartasEnLaMesa, Jugador& jugador1, Jugador& jugador2);
void GenerarCasosBase(vector<int>& cartasEnLaMesa, MatrizOpt& matrizJugadasOptimas);
void GenerarElRestoDeLosCasos(vector<int>& cartasEnLaMesa, MatrizOpt& matrizJugadasOptimas);
void PasarDeListaAVector(vector<int>& cartasEnLaMesa, list<int>& listaDeCartas);
vector<int> ObtenerSumaIzquierdaDeLasCartasEntre(int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, vector<int>& cartasEnLaMesa);
vector<int> ObtenerSumaDerechaDeLasCartasEntre(int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, vector<int>& cartasEnLaMesa);
JugadaOptima ObtenerJugadaOptimaDesdeLaIzquierda(vector<int>& sumaParcialIzquierda, int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, MatrizOpt& matrizJugadasOptimas);
JugadaOptima ObtenerJugadaOptimaDesdeLaDerecha(vector<int>& sumaParcialDerecha, int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, MatrizOpt& matrizJugadasOptimas);
timespec diff(timespec start, timespec end);
