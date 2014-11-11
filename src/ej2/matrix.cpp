#include "matrix.h"

Matrix::Matrix(const Nat dimensiones) : _altoYLargo(dimensiones), _matriz(vector<vector<pair<double,Nat> > >(dimensiones, vector<pair<double,Nat> >(dimensiones))) {}

Nat Matrix::Filas() const {
	return _altoYLargo;
}
Nat Matrix::Columnas() const {
	return _altoYLargo;
}

double Matrix::DistanciaDe(const Arista pos) const {
	return _matriz[pos.first][pos.second].first;
}

Nat Matrix::OrigenDe(const Arista pos) const {
	return _matriz[pos.first][pos.second].second;
}

void Matrix::Combinar(const Nat fila) {
	Nat dimension = Columnas();
	double inf = numeric_limits<double>::infinity();
	_matriz[0][fila].first = inf;
	for (Nat j = 0 ; j != dimension ; j++){
		Arista aristaF1 = make_pair(0,j);
		Arista aristaF2 = make_pair(fila,j);
		if (isfinite(DistanciaDe(aristaF1)) && DistanciaDe(aristaF2) < DistanciaDe(aristaF1)){
			_matriz[0][j].first = DistanciaDe(aristaF2);
			_matriz[0][j].second = OrigenDe(aristaF2);
		}
		
	}
}

Nat Matrix::MinFila(const Nat i) const {
	Nat dimension = Columnas();
	Arista min = make_pair(i,0);
	Nat res = 0;
	for (Nat j = 1 ; j < dimension ; j++){
		Arista aristaIJ = make_pair(i,j);
		if (DistanciaDe(aristaIJ) < DistanciaDe(min)){
			min = aristaIJ; 
			res = j;
		}
	
	}
//	cout << "fila:" << i << " min:" << res << endl;
	return res;
}

void Matrix::LlenarDistancias(const Nat nPueblos, const list<Coordenada>& pueblos){
	list<Coordenada>::const_iterator itI = pueblos.begin();
	list<Coordenada>::const_iterator itJ = pueblos.begin();
	for (Nat i = 0; i != nPueblos ; i++){
		double x1 = itI->first;
		double y1 = itI->second;
		for (Nat j = 0; j != nPueblos ; j++){
			double x2 = itJ->first;
			double y2 = itJ->second;
			double distancia = numeric_limits<double>::infinity();
			if (i != j){
				distancia = sqrt((x1-x2)*(x1-x2) + ((y1-y2)*(y1-y2)));
			}
			//cout << distancia << ";" << i+1 <<" ";
			_matriz[i][j].first = distancia;
			_matriz[i][j].second = i+1;
			itJ++;
		}
		//cout << endl;
		itI++;
		itJ = pueblos.begin();
	}
}

