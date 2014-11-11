#include "tipos.h"
#include "caminomin.h"
#include <cassert>

#ifndef TABLITA_H_
#define TABLITA_H_

struct LaTablita {
		
		vector<vector<vector<CaminoMin> > > distancia;
		Nat potenciaMaxima;
		
		LaTablita(Nat dimensiones, Nat potenciaExtra);
		/*Dado que esta tabla es rellenada por fuera, no conozco la posicion de origen a este nivel
		   aunque posiblemente la pueda averiguar si me interesara.
		  Es aquella en la que distancia[i][j][k].Saltos == 0 para todo k valido.
		  La lista de camino minimo va a estar ordenada de salto mas "antiguo" a salto mas "reciente",
		   es decir, en el orden pedido por el formato de salida.*/
		list<CoordenadaYPotencia> CaminoMinimo(const Coordenada pos) const;
		//bool EsCoordenadaValida(const Coordenada pos) const;
};


#endif
