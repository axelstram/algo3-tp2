#include "problema1.h"


int main(int argc, char* argv[]) {

	bool hayQueTomarMediciones = false;

	if (strcmp(argv[1], "1") == 0) {

		hayQueTomarMediciones = true;

	}

	while (cin.peek() != EOF) {

		if (hayQueTomarMediciones) {

			ResolverYTomarMedicionesDe(argv[0]+2);

		} else {

			ResolverNormalmente();

		}
		
		cin.ignore(1);
		
	}

}




void ResolverYTomarMedicionesDe(const char* nombreArchivoTest) {

	list<int> cartasEnLaMesa;
	Jugador jugador1Original;
	Jugador jugador2Original;
	int cantTurnos;

	CargarCartas(cartasEnLaMesa);

	ofstream fileMediciones;
	string nombreDeArchivo = "mediciones de ";
	nombreDeArchivo += nombreArchivoTest;
	fileMediciones.open(nombreDeArchivo, ofstream::app);
	fileMediciones << cartasEnLaMesa.size() << " ";


	timespec startT, endT; //Para calcular el tiempo
	unsigned long long int sumaNanosegundos = 0;
	unsigned long int sumaSegundos = 0;
	unsigned int cantMediciones = 20;

	for (unsigned int medicion = 1; medicion <= cantMediciones; medicion++) {

		Jugador jugador1;
		Jugador jugador2;

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startT); //comienzo a medir tiempo
		cantTurnos = Robanumeros(cartasEnLaMesa, jugador1, jugador2);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endT);	//termino de medir

		if (medicion == 1) {

			jugador1Original = jugador1;
			jugador2Original = jugador2;

		}

		timespec estaMedicion = diff(startT,endT);
		sumaNanosegundos += estaMedicion.tv_nsec;
		sumaSegundos += estaMedicion.tv_sec;

	}

	unsigned long long int promedioNanosegundos = sumaNanosegundos / cantMediciones;
	unsigned long int promedioSegundos = sumaSegundos / cantMediciones;

	fileMediciones << promedioSegundos << " " << promedioNanosegundos << endl;
	fileMediciones.close();

	ImprimirSolucion(cartasEnLaMesa, jugador1Original, jugador2Original, cantTurnos);

}






void ResolverNormalmente() {

	list<int> cartasEnLaMesa;
	Jugador jugador1;
	Jugador jugador2;
	int cantTurnos;

	CargarCartas(cartasEnLaMesa);

	cantTurnos = Robanumeros(cartasEnLaMesa, jugador1, jugador2);

	ImprimirSolucion(cartasEnLaMesa, jugador1, jugador2, cantTurnos);

}



int Robanumeros(list<int> cartasEnLaMesa, Jugador& jugador1, Jugador& jugador2) {

	bool esElTurnoDelJugador1 = true;
	bool hayCartasEnLaMesa = true;
	int cantCartas = cartasEnLaMesa.size();
	int cantTurnos = 0;
	int inicioSubsecuenciaDeCartas = 1;
	int finSubsecuenciaDeCartas = cantCartas;
	MatrizOpt matrizJugadasOptimas(cantCartas+1, vector<JugadaOptima>(cantCartas+1));

	GenerarTodasLasJugadasOptimas(cartasEnLaMesa, matrizJugadasOptimas);

	while (hayCartasEnLaMesa) {	

		if (esElTurnoDelJugador1) {

			RealizarJugadaOptimaEntre(inicioSubsecuenciaDeCartas, finSubsecuenciaDeCartas, cartasEnLaMesa, jugador1, matrizJugadasOptimas);

			esElTurnoDelJugador1 = false;

		} else {

			RealizarJugadaOptimaEntre(inicioSubsecuenciaDeCartas, finSubsecuenciaDeCartas, cartasEnLaMesa, jugador2, matrizJugadasOptimas);

			esElTurnoDelJugador1 = true;

		}

		cantTurnos++;

		hayCartasEnLaMesa = (cartasEnLaMesa.size() != 0);

	}

	return cantTurnos;

}




void GenerarTodasLasJugadasOptimas(list<int>& listaDeCartas, MatrizOpt& matrizJugadasOptimas) {

	int cantCartas = listaDeCartas.size();

	vector<int> cartasEnLaMesa(cantCartas+1, 0);

	//Paso todas las cartas de una lista a un vector, porque me es mas conveniente para las demas funciones.
	PasarDeListaAVector(cartasEnLaMesa, listaDeCartas); //O(n)

	GenerarCasosBase(cartasEnLaMesa, matrizJugadasOptimas);	//O(n)

	GenerarElRestoDeLosCasos(cartasEnLaMesa, matrizJugadasOptimas);

}


void PasarDeListaAVector(vector<int>& cartasEnLaMesa, list<int>& listaDeCartas) {

	int i = 1;

	for (list<int>::iterator it = listaDeCartas.begin(); it != listaDeCartas.end(); ++it) {	//O(n)

		cartasEnLaMesa[i] = *it;	//O(1)
		i++;						//O(1)

	}

}


void GenerarCasosBase(vector<int>& cartasEnLaMesa, MatrizOpt& matrizJugadasOptimas) {

	int cantCartas = cartasEnLaMesa.size() - 1; 

	Jugada jugada;	//<extremo, cant de cartas>
	jugada.first = "izq";
	jugada.second = 1;

	JugadaOptima jugadaOptima;	//< beneficio a mi favor, jugada que debo hacer >
	jugadaOptima.first = 0;
	jugadaOptima.second = jugada;

	matrizJugadasOptimas[0][0] = jugadaOptima;

	int i = 1;
	//Todo lo de arriba es O(1)

	for (int inicioSubsecuencia = 1; inicioSubsecuencia <= cantCartas; inicioSubsecuencia++) {	//O(n)

		int finSubsecuencia = inicioSubsecuencia;	//O(1)

		jugadaOptima.first = cartasEnLaMesa[i];		//O(1)
		matrizJugadasOptimas[inicioSubsecuencia][finSubsecuencia] = jugadaOptima;	//O(1)

		i++;

	}

}



void GenerarElRestoDeLosCasos(vector<int>& cartasEnLaMesa, MatrizOpt& matrizJugadasOptimas) {

	int n = cartasEnLaMesa.size() - 1;
	//La matriz es de (n+1)*(n+1). Por lo tanto, la secuencia entera de cartas va de 1 hasta n

	//Lleno la matriz de abajo para arriba, de izquierda a derecha
	for (int inicioSubsecuenciaDeCartas = n - 1; inicioSubsecuenciaDeCartas >= 1; inicioSubsecuenciaDeCartas--) {	//O(n³)

		for (int finSubsecuenciaDeCartas = inicioSubsecuenciaDeCartas + 1; finSubsecuenciaDeCartas <= n; finSubsecuenciaDeCartas++) {	//O(n²)

			vector<int> sumaParcialIzquierda = ObtenerSumaIzquierdaDeLasCartasEntre(inicioSubsecuenciaDeCartas, finSubsecuenciaDeCartas, cartasEnLaMesa); //O(n)
			vector<int> sumaParcialDerecha = ObtenerSumaDerechaDeLasCartasEntre(inicioSubsecuenciaDeCartas, finSubsecuenciaDeCartas, cartasEnLaMesa);   //O(n)
			
			//JugadaOptima == < beneficio a mi favor, jugada que debo hacer >
			JugadaOptima jugadaOptimaIzq = ObtenerJugadaOptimaDesdeLaIzquierda(sumaParcialIzquierda, inicioSubsecuenciaDeCartas, finSubsecuenciaDeCartas, matrizJugadasOptimas); //O(n)
			JugadaOptima jugadaOptimaDer = ObtenerJugadaOptimaDesdeLaDerecha(sumaParcialDerecha, inicioSubsecuenciaDeCartas, finSubsecuenciaDeCartas, matrizJugadasOptimas);	 //O(n)
			JugadaOptima jugadaOptima;

			if (jugadaOptimaIzq.first > jugadaOptimaDer.first) {	//O(1)

				jugadaOptima = jugadaOptimaIzq;	//O(1)

			} else {

				jugadaOptima = jugadaOptimaDer;	//O(1)

			}

			//cout << inicioSubsecuenciaDeCartas << " " << finSubsecuenciaDeCartas << " beneficio: " << jugadaOptima.first << endl;

			matrizJugadasOptimas[inicioSubsecuenciaDeCartas][finSubsecuenciaDeCartas] = jugadaOptima; //O(1)

		}

	}

}



vector<int> ObtenerSumaIzquierdaDeLasCartasEntre(int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, vector<int>& cartasEnLaMesa) {

	vector<int> sumasParciales(finSubsecuenciaDeCartas - inicioSubsecuenciaDeCartas + 2, 0); //O(n)
	//Por conveniencia lo creo de tamaño un poco mas grande, y dejo la primera posicion en cero.
	int j = 1;

	for (int i = inicioSubsecuenciaDeCartas; i <= finSubsecuenciaDeCartas; i++) {	//O(n)

		if (j == 1) {

			sumasParciales[j] = cartasEnLaMesa[i];	//O(1)

		} else {

			sumasParciales[j] = cartasEnLaMesa[i] + sumasParciales[j-1]; //O(1)

		}

		j++;

	}

	return sumasParciales;

}




vector<int> ObtenerSumaDerechaDeLasCartasEntre(int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, vector<int>& cartasEnLaMesa) {

	vector<int> sumasParciales(finSubsecuenciaDeCartas - inicioSubsecuenciaDeCartas + 2, 0); 
	//Por conveniencia lo creo de tamaño un poco mas grande, y dejo la primera posicion en cero.
	int j = 1;

	for (int i = finSubsecuenciaDeCartas; i >= inicioSubsecuenciaDeCartas; i--) {

		if (j == 1) {

			sumasParciales[j] = cartasEnLaMesa[i];

		} else {

			sumasParciales[j] = cartasEnLaMesa[i] + sumasParciales[j-1];

		}

		j++;

	}

	return sumasParciales;

}




JugadaOptima ObtenerJugadaOptimaDesdeLaIzquierda(vector<int>& sumaParcialIzquierda, int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, MatrizOpt& matrizJugadasOptimas) {

	assert(inicioSubsecuenciaDeCartas <= finSubsecuenciaDeCartas && "acceso a subsecuencia invalida");

	int cantCartas = sumaParcialIzquierda.size() - 1;	//O(1)
	JugadaOptima jugadaOptima;  //< beneficio a mi favor, jugada que debo hacer >	//O(1)
	Jugada jugada; //<extremo, cant de cartas>	//O(1)
	jugada.first = "izq";						//O(1)
	int mayorBeneficioAFavor = 0;	//O(1)
	bool todaviaNoCalculeNingunBeneficio = true;	//O(1)
		
	for (int cantCartasAgarradas = 1; cantCartasAgarradas <= cantCartas; cantCartasAgarradas++) {	//O(cantCartas) = O(n)

		int sumaDeLasPrimerasICartas = sumaParcialIzquierda[cantCartasAgarradas];	//O(1)
		int mayorBeneficioDelOponente;	//O(1)

		//cout << inicioSubsecuenciaDeCartas << " " << finSubsecuenciaDeCartas << " cantCartasAgarradasIzq: " << cantCartasAgarradas << " suman " << sumaDeLasPrimerasICartas << endl;

		if (cantCartasAgarradas < cantCartas) {	//O(1)
			//El beneficio del oponente es lo mejor que se puede sacar de la subsecuencia de cartas restante.
			mayorBeneficioDelOponente = matrizJugadasOptimas[inicioSubsecuenciaDeCartas+cantCartasAgarradas][finSubsecuenciaDeCartas].first;	//O(1)

		} else {
			//Si agarre todas las cartas, el beneficio del oponente obviamente es 0.
			mayorBeneficioDelOponente = 0;	//O(1)

		}

		if (todaviaNoCalculeNingunBeneficio) {	//O(1)
			//Como todavia no tengo ningun beneficio a favor, agarro el primero que calculo y lo tomo como maximo
			mayorBeneficioAFavor = sumaDeLasPrimerasICartas - mayorBeneficioDelOponente;	//O(1)
			todaviaNoCalculeNingunBeneficio = false;	//O(1)

		}

		if (mayorBeneficioAFavor <= sumaDeLasPrimerasICartas - mayorBeneficioDelOponente) {	//O(1)
			//Actualizo cual seria mi mejor jugada
			mayorBeneficioAFavor = sumaDeLasPrimerasICartas - mayorBeneficioDelOponente;	//O(1)
			
			jugada.second = cantCartasAgarradas;		//O(1)

			jugadaOptima.first = mayorBeneficioAFavor;	//O(1)
			jugadaOptima.second = jugada;				//O(1)

		}

	}

	return jugadaOptima;	

}





JugadaOptima ObtenerJugadaOptimaDesdeLaDerecha(vector<int>& sumaParcialDerecha, int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, MatrizOpt& matrizJugadasOptimas) {

	assert(inicioSubsecuenciaDeCartas <= finSubsecuenciaDeCartas && "acceso a subsecuencia invalida");

	int cantCartas = sumaParcialDerecha.size() - 1;

	JugadaOptima jugadaOptima;  //< beneficio a mi favor, jugada que debo hacer >
	Jugada jugada; //<extremo, cant de cartas>
	jugada.first = "der";
	int mayorBeneficioAFavor = 0;
	bool todaviaNoCalculeNingunBeneficio = true;

	for (int cantCartasAgarradas = 1; cantCartasAgarradas <= cantCartas; cantCartasAgarradas++) {

		int sumaDeLasPrimerasICartas = sumaParcialDerecha[cantCartasAgarradas];
		int mayorBeneficioDelOponente;
		
		//cout << inicioSubsecuenciaDeCartas << " " << finSubsecuenciaDeCartas << " cantCartasAgarradasDer: " << cantCartasAgarradas << " suman " << sumaDeLasPrimerasICartas << endl;

		if (cantCartasAgarradas < cantCartas) {
			//El beneficio del oponente es lo mejor que se puede sacar de la subsecuencia de cartas restante.
			mayorBeneficioDelOponente = matrizJugadasOptimas[inicioSubsecuenciaDeCartas][finSubsecuenciaDeCartas-cantCartasAgarradas].first;

		} else {
			//Si agarre todas las cartas, el beneficio del oponente obviamente es 0.
			mayorBeneficioDelOponente = 0;

		}	


		if (todaviaNoCalculeNingunBeneficio) {
			//Como todavia no tengo ningun beneficio a favor, agarro el primero que calculo y lo tomo como maximo
			mayorBeneficioAFavor = sumaDeLasPrimerasICartas - mayorBeneficioDelOponente;
			todaviaNoCalculeNingunBeneficio = false;

		}


		if (mayorBeneficioAFavor <= sumaDeLasPrimerasICartas - mayorBeneficioDelOponente) {
			//Actualizo cual seria mi mejor jugada
			mayorBeneficioAFavor = sumaDeLasPrimerasICartas - mayorBeneficioDelOponente;
			
			jugada.second = cantCartasAgarradas;

			jugadaOptima.first = mayorBeneficioAFavor;
			jugadaOptima.second = jugada;

		}

	}

	return jugadaOptima;

}



void RealizarJugadaOptimaEntre(int& inicioSubsecuenciaDeCartas, int& finSubsecuenciaDeCartas, list<int>& cartasEnLaMesa, Jugador& jugador, MatrizOpt& matrizJugadasOptimas) {

	Jugada jugada = ObtenerMejorJugadaEntre(inicioSubsecuenciaDeCartas, finSubsecuenciaDeCartas, matrizJugadasOptimas);	//O(1)

	string extremoDeDondeSaco = jugada.first;	//O(1)
	int cantCartasQueSaco = jugada.second;		//O(1)

	if (extremoDeDondeSaco == "izq") {			//O(1)

		inicioSubsecuenciaDeCartas += cantCartasQueSaco;	//O(1)

	} else {

		finSubsecuenciaDeCartas -= cantCartasQueSaco;		//O(1)

	}
	
	jugador.AgregarJugada(jugada); //O(1)

	ActualizarPuntajeJugador(cartasEnLaMesa, jugador, jugada); //O(n)

}



void ActualizarPuntajeJugador(list<int>& cartasEnLaMesa, Jugador& jugador, Jugada jugada) {

	string extremoDeDondeSaco = jugada.first;	//O(1)
	int cantCartasARemover = jugada.second;		//O(1)
	int puntos;

	for (int cantCartas = 0; cantCartas < cantCartasARemover; cantCartas++) {	//O(cantCartasARemover) = O(n)

		if (extremoDeDondeSaco == "izq") {	//O(1)

			puntos = cartasEnLaMesa.front();	//O(1)
			cartasEnLaMesa.pop_front();			//O(1)

		} else {

			puntos = cartasEnLaMesa.back();		//O(1)
			cartasEnLaMesa.pop_back();			//O(1)

		}

		jugador.AgregarPuntos(puntos);			//O(1)

	}

}


Jugada ObtenerMejorJugadaEntre(int inicioSubsecuenciaDeCartas, int finSubsecuenciaDeCartas, MatrizOpt& matrizJugadasOptimas) {

	assert(inicioSubsecuenciaDeCartas <= finSubsecuenciaDeCartas && "acceso a subsecuencia invalida");

	return matrizJugadasOptimas[inicioSubsecuenciaDeCartas][finSubsecuenciaDeCartas].second;	//O(1)

}


void CargarCartas(list<int>& cartasEnLaMesa) {
	
	int carta;
	int cantCartas;
	
    cin >> cantCartas;	

	for (int i = 1; i <= cantCartas; i++) {

		cin >> carta;

		cartasEnLaMesa.push_back(carta);

	}

}

void ImprimirSolucion(list<int>& cartasEnLaMesa, Jugador& jugador1, Jugador& jugador2, int cantTurnos) {

	cout << cantTurnos << " " << jugador1.ObtenerPuntos() << " " << jugador2.ObtenerPuntos() << endl;

	int nroJugada = 0;

	for (int i = 0; i < cantTurnos; i+= 2) {

		jugador1.ImprimirJugada(nroJugada);
		jugador2.ImprimirJugada(nroJugada);

		nroJugada++;

	}

}



timespec diff(timespec start, timespec end) {
    timespec temp;

    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }

    return temp;
}

