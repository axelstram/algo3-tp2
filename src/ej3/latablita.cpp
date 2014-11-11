#include "latablita.h"

// Poniendolo en terminos mas claros, esta tablita es una matriz de k+1 tableros de Matrix.
// La diferencia principal es que voy a guardar el resultado de g(p,k_i) para todos los valores del dominio en lugar de la potencia inherente del casillero.
// Ademas, por conveniencia se indiza primero por las coordenadas del tablero y luego por la potencia restante.
// Entonces, tecnicamente tengo una matriz de las dimensiones del tablero de Matrix pero cuyo contenido es un vector de CaminoMin.
LaTablita::LaTablita(Nat dimensiones, Nat potenciaExtra) : distancia(dimensiones, vector<vector<CaminoMin> >(dimensiones, vector<CaminoMin>(potenciaExtra+1))), potenciaMaxima(potenciaExtra) {}

//Pre: Ya esta definido un camino desde esa coordenada hasta el origen. Si alguien recorre mal la tabla, hay tabla. Y si no, tambien.
list<CoordenadaYPotencia> LaTablita::CaminoMinimo(const Coordenada pos) const {
	CaminoMin este;
	Nat potenciaFinal = 0;
	//Consigo el minimo camino consultando las k posiciones del vector que le corresponde.
	//Como usamos BFS, hay sólo una posición definida.
	for (Nat k = 0; k <= potenciaMaxima; k++) {
		const vector<CaminoMin>& caminos = distancia[pos.first-1][pos.second-1];
		if (caminos[k].Saltos != -1) {
			este = caminos[k];
			potenciaFinal = k;
			break;
		}
	}
	
	assert(este.Saltos != -1);
	
	//Reconstruyo la secuencia de saltos.
	list<CoordenadaYPotencia> res;
	CoordenadaYPotencia paso;
	paso.first = pos;
	paso.second = este.potenciaUsada;
	while (este.Saltos > 0) {
		res.push_front(paso);
		potenciaFinal += este.potenciaUsada;
		Coordenada anterior = este.CasilleroAnterior;
		este = distancia[anterior.first-1][anterior.second-1][potenciaFinal];
		paso.first = anterior;
		paso.second = este.potenciaUsada;
	}
	return res;
}
