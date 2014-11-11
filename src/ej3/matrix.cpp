#include "matrix.h"

Matrix::Matrix(const Nat dimensiones, const Matriz& casilleros) : _altoYLargo(dimensiones), _matriz(casilleros) {}

Nat Matrix::Filas() const {
	return _altoYLargo;
}
Nat Matrix::Columnas() const {
	return _altoYLargo;
}

Nat Matrix::PotenciaDe(const Coordenada pos) const {
	return _matriz[pos.first-1][pos.second-1];
}

bool Matrix::EsCoordenadaValida(const Coordenada pos) const {
	int dimension = Filas();
	if (0 >= pos.first || pos.first > dimension) {
		return false;
	}
	if (0 >= pos.second || pos.second > dimension) {
		return false;
	}
	return true;
}

