#include "problema2.h"
int main() {
	//Al final de cada parametro debe ir un caracter de nueva linea.
	//Primer parametro: "-nombre" donde nombre es el nombre del archivo donde se quiere que se guarden los resultados . Si no se pasa un parametro de este tipo entonces no se toman mediciones.
	
	//Si hay un guion, esta el primer parámetro y tengo que tomar mediciones.
	bool hayQueTomarMediciones = false;
	string nombreDeArchivo;
	if (cin.peek() == '-') {
		cin.ignore(1,'-');
		getline(cin, nombreDeArchivo);
		hayQueTomarMediciones = true;
	}
	do {
		list<Coordenada> pueblos;
		Nat nPueblos, kCentrales;
		cin >> nPueblos >> kCentrales;

		//assert(nPueblos > 0);
		if (nPueblos==0) {
			cerr << "No hay pueblos en el mapa." << endl;
			exit(EXIT_FAILURE);
		}
		//assert(kCentrales > 0);
		if (kCentrales==0) {
			cerr << "No hay centrales de gas." << endl;
			exit(EXIT_FAILURE);
		}
		//el Maximo de centrales que pondremos es el numero de pueblos, asi que si es mayor lo achicamos
		if (nPueblos < kCentrales){
			kCentrales = nPueblos;
		}

		//Agrego las coordenadas de los pueblos a una lista
		for (Nat i=0 ; i < nPueblos ; i++){
			int x, y;
			cin >> x >> y;
			Coordenada parXY = make_pair(x,y);
			pueblos.push_back(parXY);
		}
		//RESOLUCION
		resolver(nPueblos , kCentrales , pueblos , true);
		//TOMA DE MEDICIONES
		if (hayQueTomarMediciones) {
			timespec startT, endT; //Para calcular el tiempo
			ofstream fileMediciones;
			string guardarEn = "mediciones de ";
			guardarEn += nombreDeArchivo;
			guardarEn += ".xls";
			fileMediciones.open(guardarEn, ofstream::app); //append
			unsigned long long int sumaNanosegundos = 0;
			long double sumaSegundos = 0;
			Nat cantMediciones = 50; //50 mínimo
			for(Nat medicion = 1; medicion <= cantMediciones; medicion++) {
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startT); //comienzo a medir tiempo
				resolver(nPueblos , kCentrales , pueblos , false);
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endT);	//termino de medir
				timespec estaMedicion = diff(startT,endT);
				sumaNanosegundos += estaMedicion.tv_nsec;
				sumaSegundos += estaMedicion.tv_sec;
			}
			unsigned long long int promedioNanosegundos = sumaNanosegundos / cantMediciones;
			long double promedioSegundos = sumaSegundos / cantMediciones;
			fileMediciones << nPueblos << " " << promedioSegundos << " " << promedioNanosegundos << endl;
			fileMediciones.close();
		}
	}while ((cin.peek() != EOF) && (hayQueTomarMediciones));
	return 0;
}
void resolver(Nat nPueblos, Nat kCentrales, list<Coordenada>& pueblos, bool mostrarResultado){
	
	Matrix tablaDistancias (nPueblos);
	tablaDistancias.LlenarDistancias(nPueblos, pueblos);
	list<pair<Arista,double> > bosqueMinimo;
	for (Nat i=1; i < nPueblos; i++) {
		Nat j = tablaDistancias.MinFila(0);
		Arista parXY = make_pair(0,j);
		double distancia = tablaDistancias.DistanciaDe(parXY);
		//cout << "la distancia es " << distancia << endl;
		Nat origen = tablaDistancias.OrigenDe(parXY);
		//cout << "el origen es " << origen << endl;
		parXY = make_pair(j+1,origen);
		pair<Arista,double> parPosDist = make_pair(parXY,distancia);
		bosqueMinimo.push_front(parPosDist);
		tablaDistancias.Combinar(j);
		
	}
	//VEASE QUE HASTA ESTE PUNTO BOSQUE MINIMO ES UN ARBOL MINIMO
	bosqueMinimo.sort(ordenPares);
	// Para crear k arboles quiero sacar las k-1 aristas de mayor tamaño
	Nat tamano = bosqueMinimo.size();

	// If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
	bosqueMinimo.resize(tamano-(kCentrales-1));
	Nat cantidadTuberias = bosqueMinimo.size();
	list<Nat> estaciones = generarEstaciones(bosqueMinimo , nPueblos);
	if (mostrarResultado){
	mostrar(kCentrales, cantidadTuberias , estaciones, bosqueMinimo);
	}
}

bool ordenPares (const pair<Arista,double>& par1, const pair<Arista,double>& par2){
	bool res = false;
	if (par1.second < par2.second) res = true;
	return res;
}


list<Nat> generarEstaciones(list<pair<Arista,double> > bosqueMinimo, Nat nPueblos){
	list<Nat> res;
	vector<bool> yaLoVi (nPueblos, false);
	vector<bool> conectados (nPueblos, false);
	list<Nat> proximosVer;
	for (Nat i=0 ; i < nPueblos ; i++){
		proximosVer.push_back(i+1);
	}
	while (!proximosVer.empty()){
		Nat sacar = proximosVer.front();
		if (yaLoVi[sacar]){
			proximosVer.pop_front();
		}else{
			if (!conectados[sacar]){
				res.push_back(sacar);
			}
			proximosVer.pop_front();
			conectados[sacar] = true;
			yaLoVi[sacar] = true;
			list<pair<Arista,double> >::iterator itAM = bosqueMinimo.begin();
			while (itAM != bosqueMinimo.end() && bosqueMinimo.size() != 0){
				if (itAM->first.first == sacar){
					Nat j = itAM->first.second;
					if (!conectados[j]){
						proximosVer.push_front(j);
						conectados[j] = true;
					}
					itAM = bosqueMinimo.erase(itAM);
				}else if (itAM->first.second == sacar){
					Nat j = itAM->first.first;
					if (!conectados[j]){
						proximosVer.push_front(j);
						conectados[j]=true;
					}
					itAM = bosqueMinimo.erase(itAM);
				}else{
					itAM++;
				}
			}
		}
		
	}
	return res;
}

void mostrar(Nat kCentrales, Nat cantidadTuberias, list<Nat> estaciones, list<pair<Arista,double> >& bosqueMinimo) {

	cout << kCentrales << " " << cantidadTuberias << " " << endl;

	list<Nat>::iterator itEst = estaciones.begin();
	cout << *itEst;
	itEst++;
	for (Nat i = 1; i !=kCentrales; i++) {
		cout << " " << *itEst ;
		itEst++;
	}
	cout << endl;
	
	list<pair<Arista,double> >::iterator itCT = bosqueMinimo.begin();
	for (Nat i = 0; i !=cantidadTuberias; i++) {
		Nat pueblo1 = itCT->first.first;
		Nat pueblo2 = itCT->first.second;
		cout << pueblo1 << " " << pueblo2 << endl;
		itCT++;
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


