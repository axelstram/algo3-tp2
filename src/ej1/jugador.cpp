#include "jugador.h"

Jugador::Jugador() {

	_cantPuntos = 0;

}


void Jugador::AgregarPuntos(int puntos) {

	_cantPuntos += puntos;

}


int Jugador::ObtenerPuntos() const {

	return _cantPuntos;

}


void Jugador::AgregarJugada(Jugada jugada) {

	_jugadas.push_back(jugada);

}


void Jugador::ImprimirJugada(int nroJugada) {

	int i = 0;

	for (list<Jugada>::iterator it = _jugadas.begin(); it != _jugadas.end(); ++it) {

		Jugada jugada = *it;

		if (i == nroJugada) {

			cout << jugada.first << " " << jugada.second << endl;
			break;

		}

		i++;
		
	}

}

