#include <utility>
#include <list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



#ifndef JUGADAS
#define JUGADAS

typedef pair<string, int> Jugada;			//<extremo, cant de cartas>

#endif



#ifndef JUGADOR
#define JUGADOR

class Jugador {

	private:

		int _cantPuntos;
		list<Jugada> _jugadas;

	public:

		Jugador();
		void AgregarPuntos(int puntos);
		int ObtenerPuntos() const;
		void AgregarJugada(Jugada j);
		void ImprimirJugada(int nroJugada);

};

#endif