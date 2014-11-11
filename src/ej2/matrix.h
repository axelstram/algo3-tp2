#include "tipos.h"
#include <math.h>
#include <limits>


#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {

	private:

		Nat _altoYLargo;
		Matriz _matriz;

	public:

		Matrix(const Nat dimensiones);
		double DistanciaDe(const Arista pos) const;
		Nat OrigenDe(const Arista pos) const;
		void Combinar(const Nat fila);
		Nat MinFila(const Nat i) const;
		void LlenarDistancias(const Nat nPueblos, const list<Coordenada>& pueblos);
		Nat Filas() const;
		Nat Columnas() const;

};


#endif
