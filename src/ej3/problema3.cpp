#include "problema3.h"




int main(int argc, char** argv) {
	//Al final de cada parametro debe ir un caracter de nueva linea.
	//Primer parametro: el nombre del archivo donde se quiere que se guarden los resultados . Si no se pasa un parametro de este tipo entonces no se toman mediciones.
	if (argc > 2) {
		cerr << "Demasiados parametros." << endl;
		exit(EXIT_FAILURE);
	}
	
	//Si hay un guion, está el primer parámetro y tengo que tomar mediciones.
	if (argc == 2) {
		string nombreDeArchivo = argv[1];
		MedirTiempo(nombreDeArchivo);
	} else
		ResolverNormalmente();
	exit(EXIT_SUCCESS);
}

void MedirTiempo(string& nombreDeArchivo) {
	//Para medir tiempos leemos varias instancias de un solo archivo, con lo cual el formato de entrada difiere un poco del especificado.
	//Luego de cada instancia puede venir otra instancia más o un 0 en una nueva línea. El 0 indica que ya no hay más instancias para cargar.
	while (cin.good()) {
		Nat n;
		cin >> n;

		if (cin.fail()) {
			cerr << "No se pudieron leer las dimensiones de la matrix." << endl;
			exit(EXIT_FAILURE);
		} else if (n == 0) //Acá salgo porque ya resolví la última instancia.
			break;
		
		Nat x, y;
		cin >> x >> y;
		if (!cin.good()) {
			cerr << "No se pudieron leer las coordenadas de origen." << endl;
			exit(EXIT_FAILURE);
		}
		if (x > n || y > n || x == 0 || y == 0) {
			cerr << "Coordenadas de origen invalidas." << endl;
			exit(EXIT_FAILURE);
		}
		Coordenada origen(x, y);
		
		cin >> x >> y;
		if (!cin.good()) {
			cerr << "No se pudieron leer las coordenadas de destino." << endl;
			exit(EXIT_FAILURE);
		}
		if (x > n || y > n || x == 0 || y == 0) {
			cerr << "Coordenadas de destino invalidas." << endl;
			exit(EXIT_FAILURE);
		}
		Coordenada destino(x, y);
		
		Nat potenciaExtra;
		cin >> potenciaExtra;
		if (!cin.good()) {
			cerr << "No se pudo leer la cantidad de unidades de potencia extra." << endl;
			exit(EXIT_FAILURE);
		}
		cin.ignore(1, '\n');
		
		//Inicializamos la matriz y el tablero.
		Matriz casilleros(n, vector<Nat>(n));
		CargarCasilleros(n, casilleros);
		const Matrix laMatrix(n, casilleros);
		list<CoordenadaYPotencia> solucion;

		ofstream fileMediciones;
		fileMediciones.open(nombreDeArchivo, ofstream::app); //append
		timespec startT, endT; //Para calcular el tiempo
		unsigned long long int sumaNanosegundos = 0;
		long double sumaSegundos = 0;
		Nat cantMediciones = 50;

		for(Nat medicion = 1; medicion <= cantMediciones; medicion++) {
			//Limpio la lista con la solucion ya obtenida.
			solucion.clear();
			
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startT); //comienzo a medir tiempo
			solucion = Resolver(laMatrix, potenciaExtra, origen, destino);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endT);	//termino de medir
						
			timespec estaMedicion = diff(startT,endT);
			sumaNanosegundos += estaMedicion.tv_nsec;
			sumaSegundos += estaMedicion.tv_sec;
		}
		unsigned long long int promedioNanosegundos = sumaNanosegundos / cantMediciones;
		long double promedioSegundos = sumaSegundos / cantMediciones;

		fileMediciones << n << " " << potenciaExtra << " " << promedioSegundos << " " << promedioNanosegundos << endl;
		fileMediciones.close();
		Imprimir(solucion); //Con esto sabemos que esta trabajando.
	}
}

void ResolverNormalmente() {
	Nat n;
	cin >> n;

	if (!cin.good()) {
		cerr << "No se pudieron leer las dimensiones de la matrix." << endl;
		exit(EXIT_FAILURE);
	} else if (n == 0) {
		cerr << "Dimensiones nulas en la matrix." << endl;
		exit(EXIT_FAILURE);
	}
	
	Nat x, y;
	cin >> x >> y;
	if (!cin.good()) {
		cerr << "No se pudieron leer las coordenadas de origen." << endl;
		exit(EXIT_FAILURE);
	}
	if (x > n || y > n || x == 0 || y == 0) {
		cerr << "Coordenadas de origen invalidas." << endl;
		exit(EXIT_FAILURE);
	}
	Coordenada origen(x, y);
	
	cin >> x >> y;
	if (!cin.good()) {
		cerr << "No se pudieron leer las coordenadas de destino." << endl;
		exit(EXIT_FAILURE);
	}
	if (x > n || y > n || x == 0 || y == 0) {
		cerr << "Coordenadas de destino invalidas." << endl;
		exit(EXIT_FAILURE);
	}
	Coordenada destino(x, y);
	
	Nat potenciaExtra;
	cin >> potenciaExtra;
	if (!cin.good()) {
		cerr << "No se pudo leer la cantidad de unidades de potencia extra." << endl;
		exit(EXIT_FAILURE);
	}
	cin.ignore(1, '\n');
	
	//Inicializamos la matriz y el tablero.
	Matriz casilleros(n, vector<Nat>(n));
	CargarCasilleros(n, casilleros);
	const Matrix laMatrix(n, casilleros);
	
	list<CoordenadaYPotencia> solucion = Resolver(laMatrix, potenciaExtra, origen, destino);
	
	//Imprimo la secuencia de saltos.
	Imprimir(solucion);
}

void CargarCasilleros(const Nat n, Matriz& casilleros) {
	for (Nat i = 0; i < n; i++) {
		string str;
		getline(cin, str);
		stringstream linea(str);
		for (Nat j = 0; j < n; j++) {
			Nat potencia;
			linea >> potencia;
			casilleros[i][j] = potencia;
		}
	}
}

list<CoordenadaYPotencia> Resolver(const Matrix& laMatrix, const Nat potenciaExtra, const Coordenada origen, const Coordenada destino) {
	LaTablita tabla(laMatrix.Filas(), potenciaExtra);
	
	//Relleno la tabla para el caso base.
	tabla.distancia[origen.first-1][origen.second-1][potenciaExtra].Saltos = 0;
	
	/*Llenar la tabla tiene una complejidad en el orden de n^2*k*n.
	  Nos queda O(n^3*k).
	*/
	//Lleno la tabla partiendo desde el punto de origen.
	list<CoordenadaYPotencia> puntosPorVer;
	ObtenerYMarcarPuntosAdyacentes(puntosPorVer, tabla, laMatrix, origen, destino, potenciaExtra);
	//Este ciclo itera n^2*k veces en el peor caso. k veces por cada casillero. Algunos casilleros pueden aparecer menos de k veces.
	//Invariante: ya calcule y almacene el camino minimo al punto que estoy por ver(puntosPorVer.front()).
	while (!puntosPorVer.empty()) {
		Coordenada pos(puntosPorVer.front().first);
		Nat potenciaDisponible(puntosPorVer.front().second);
		puntosPorVer.pop_front();
		ObtenerYMarcarPuntosAdyacentes(puntosPorVer, tabla, laMatrix, pos, destino, potenciaDisponible);
	}
	//Reconstruir el camino minimo cuesta O(n+k).
	return (tabla.CaminoMinimo(destino));
}

void ObtenerYMarcarPuntosAdyacentes(list<CoordenadaYPotencia>& lista, LaTablita& tabla, const Matrix& laMatrix, const Coordenada posDeSalto, const Coordenada destinoAbsoluto, const Nat potenciaDisponible) {
	//O(n+min(k, n)) es O(n)
	const int potencia = laMatrix.PotenciaDe(posDeSalto);
	//Agrego y marco los saltos comunes.
	//Itera O(n) veces.
	for (int i = -potencia; i <= potencia; i++) {
		Coordenada posDestino = make_pair(posDeSalto.first+i, posDeSalto.second);
		MarcarYAgregar(laMatrix, lista, posDeSalto, posDestino, tabla, potenciaDisponible, 0);
		if (posDestino == destinoAbsoluto) {
			//Borro la lista porque ya no necesito ver el resto de los nodos.
			lista.clear();
			return;
		}
		
		posDestino.first = posDeSalto.first;
		posDestino.second += i;
		MarcarYAgregar(laMatrix, lista, posDeSalto, posDestino, tabla, potenciaDisponible, 0);
		if (posDestino == destinoAbsoluto) {
			//Borro la lista porque ya no necesito ver el resto de los nodos.
			lista.clear();
			return;
		}
	}
	//Ahora agrego y marco los saltos potenciados. Son no mas de cuatro casilleros por cada valor de potencia.
	//Itera O(min(k, n)) veces.
	for (Nat potenciaExtra = 1; potenciaExtra <= potenciaDisponible; potenciaExtra++) {
		const Nat potenciaTotal = potencia + potenciaExtra;
		Coordenada posDestino = make_pair(posDeSalto.first-potenciaTotal, posDeSalto.second);
		MarcarYAgregar(laMatrix, lista, posDeSalto, posDestino, tabla, potenciaDisponible, potenciaExtra);
		if (posDestino == destinoAbsoluto) {
			//Borro la lista porque ya no necesito ver el resto de los nodos.
			lista.clear();
			return;
		}
		
		posDestino.first += 2*potenciaTotal;
		MarcarYAgregar(laMatrix, lista, posDeSalto, posDestino, tabla, potenciaDisponible, potenciaExtra);
		if (posDestino == destinoAbsoluto) {
			//Borro la lista porque ya no necesito ver el resto de los nodos.
			lista.clear();
			return;
		}
		
		posDestino.first = posDeSalto.first;
		posDestino.second -= potenciaTotal;
		MarcarYAgregar(laMatrix, lista, posDeSalto, posDestino, tabla, potenciaDisponible, potenciaExtra);
		if (posDestino == destinoAbsoluto) {
			//Borro la lista porque ya no necesito ver el resto de los nodos.
			lista.clear();
			return;
		}
		
		posDestino.second += 2*potenciaTotal;
		MarcarYAgregar(laMatrix, lista, posDeSalto, posDestino, tabla, potenciaDisponible, potenciaExtra);
		if (posDestino == destinoAbsoluto) {
			//Borro la lista porque ya no necesito ver el resto de los nodos.
			lista.clear();
			return;
		}
	}
}

void MarcarYAgregar(const Matrix& laMatrix, list<CoordenadaYPotencia>& lista, const Coordenada posOrigen, const Coordenada posDestino, LaTablita& tabla, const Nat potenciaDisponible, const Nat potenciaExtra) {
	//Para no recargar el código de ObtenerYMarcarPuntosAdyacentes filtro acá coordenadas inválidas.
	if (!laMatrix.EsCoordenadaValida(posDestino)) {
		return;
	}

	// Todas las operaciones son O(1).
	const CaminoMin& origen = tabla.distancia[posOrigen.first-1][posOrigen.second-1][potenciaDisponible];
	CaminoMin& destino = tabla.distancia[posDestino.first-1][posDestino.second-1][potenciaDisponible-potenciaExtra];
	/*Si no esta marcado lo encolo para calcular los saltos desde esta posicion. Esto funciona porque es un BFS.
	  Esto significa que para cuando obtengo y marco los puntos adyacentes al punto en cuestion, 
	  ya voy a haber encontrado el camino minimo hasta el.
	*/
	if (destino.Saltos == -1)
		lista.push_back(make_pair(posDestino, potenciaDisponible-potenciaExtra));
	if (destino.Saltos == -1 || destino.Saltos > origen.Saltos+1) {
		//Marco o actualizo el punto.
		destino.Saltos = origen.Saltos+1;
		destino.CasilleroAnterior = posOrigen;
		destino.potenciaUsada = potenciaExtra;
	}
}

void Imprimir(list<CoordenadaYPotencia>& solucion) {
	cout << solucion.size() << endl;
	for (list<CoordenadaYPotencia>::iterator it = solucion.begin(); it != solucion.end(); it++)
		cout << it->first.first << ' ' << it->first.second << ' ' << it->second << endl;
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

