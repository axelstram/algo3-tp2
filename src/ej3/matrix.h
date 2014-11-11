#include "tipos.h"


#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {

	private:

		Nat _altoYLargo;
		Matriz _matriz;

	public:

		Matrix(const Nat dimensiones, const Matriz& casilleros);
		
		Nat Filas() const;
		Nat Columnas() const;
		Nat PotenciaDe(const Coordenada pos) const;
		//PuntosAdyacentes devuelve los puntos alcanzables en la coordenada dada si potenciaExtra es 0 o, en caso contrario, aquellos que se alcanzarian usando exactamente esa potencia. Esto es, si potenciaExtra es 1 y la potencia del casillero es 2, entonces se devuelve la lista de, como mucho, cuatro casilleros que estan a distancia 3.
		//void PuntosAdyacentes(const Coordenada, const Nat potenciaExtra, list<Coordenada>& lista) const;
		//bool EsPuntoAdyacente(const Coordenada pos, const Nat potenciaExtra) const;
		bool EsCoordenadaValida(const Coordenada pos) const;
		//void Mostrar() const;
};


#endif
