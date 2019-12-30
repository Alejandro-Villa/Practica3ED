/**
 * @file nutricion_receta.cpp
 * @brief Programa que muestra datos sobre una lista de recetas y calcula un
 * subconjunto de ellas siguiendo un criterio.
 *
 * Concretamente, el criterio es hallar el subconjunto de recetas que, sin
 * superar un valor calórico total, tienen la mejor proporción Proteínas 
 * frente a Hidratos de Carbono. Usamos para esto un algoritmo @a Greedy.
 */

#include "ingredientes.h"
#include "receta.h"
#include "recetas.h"
#include<fstream>
#include<algorithm>

using namespace std;

/**
 * @brief Comparación con los criterios de Proteinas/HC.
 *
 * Compara dos recetas según los criterios nutritivos del guión.
 *
 * @param "const pair<receta, double> primero" El primer elemento.
 * @param "const pair<receta, double> segundo" El segundo elemento.
 * @retval "True" si @a primero debe ir antes en la ordenación.
 * @retval "False" si @a primero debe ir después en la ordenanción.
 */
bool comparaProtHc(const pair<receta, double> primero, pair<receta, double> segundo) {
	return (primero.first.getProteinas() / primero.first.getHc()) > (segundo.first.getProteinas() / segundo.first.getHc());
}

/**
 * @brief Construye un vector de recetas candidatas, esto es, que cumplen el criterio.
 *
 * Usando el objeto recetas y teniendo el valor máximo de calorías, 
 * construimos un vector de parejas de receta y double, donde se guarda el 
 * elemento y su valor calórico.
 *
 * @param "const recetas& datos" Todas las recetas que tomamos como datos.
 * @param "const double& maximo" Máximo valor calórico de los candidatos.
 * @retval vector de parejas de los candidatos con calorias <= maximo
 */
vector<pair<receta, double>> construyeCandidatos(const recetas& datos, const double& maximo){
	vector<pair<receta, double>> candidatos;

	for (auto i=datos.begin(); i != datos.end(); ++i)
		if ((*i).getCalorias() <= maximo) {
			candidatos.push_back(make_pair((*i), (*i).getCalorias()));
		}
	
	sort(candidatos.begin(), candidatos.end(), comparaProtHc);
	
	return candidatos;
}

/**
 * @brief Comprueba si un objeto recetas es solución.
 *
 * Comprueba si el conjunto recetas tiene un valor calórico total menor 
 * que @a maximo
 *
 * @param "const recetas& posible" Conjuto que comprobaremos.
 * @param "const double& maximo" Máximo de calorías.
 * @retval "True" si @a posible es solución
 * @retval "False" si @a posible no es solución
 */
bool esSolucion(const recetas& posible, const double& maximo) {
	double suma=0;
	for (auto i = posible.begin(); i != posible.end(); ++i)
		suma+=(*i).getCalorias();

	return true?(suma <= maximo):false;
}

/**
 * @brief Algoritmo Greedy
 *
 * Halla el sobconjunto óptimo de recetas cuyo valor calórico total es menor
 * que @a maximo y que tengan el mayor valor de Proteinas/HC posible.
 * Para ello los ordenamos por "densidad" de proteínas y escogemos 
 * repetidamente el mayor.
 *
 * @retval "recetas" Las recetas que cumplen las condiciones
 * @param "const recetas& datos" Todas las recetas.
 * @param "const double& maximo" El máximo valor calórico.
 */
recetas solucionGreedy(const recetas& datos, const double& maximo) {
	vector<pair<receta, double>> candidatos(construyeCandidatos(datos, maximo));
	recetas solucion;

	while (!candidatos.empty()) {
		pair<receta, double> seleccionado = candidatos.front();
		candidatos.erase(candidatos.begin());

		recetas parcial(solucion);
		parcial.addReceta(seleccionado.first);
		
		if(esSolucion(parcial, maximo))
			solucion.addReceta(seleccionado.first);
	}

	if(esSolucion(solucion, maximo))
		return solucion;
}

int main(int argc, char* argv[]) {
	if(argc != 4) {
		cerr << "Llamada al programa incorrecta." << endl;
		exit(EXIT_FAILURE);
	}
	else {
		string freceta = argv[1], fingre = argv[2], valor = argv[3];
		const double MAX_CAL = stod(valor);
		ifstream fr(freceta), fi(fingre);

		if(!fr || !fi) {
			cerr << "Error en apertura de archivos..." << endl;
			exit(EXIT_FAILURE);
		}

		ingredientes all_ingre;
		fi >> all_ingre;

		recetas rall;
		fr >> rall;
		
		rall.setNutrientes(all_ingre);

		for (auto i = rall.begin(); i != rall.end(); ++i) {
			cout << "Los valores nutricionales de la receta " << (*i) << " son: " << endl;
			cout << "Calorías " << (*i).getCalorias() << "\tHidratos de Carbono " << (*i).getHc() << "\tProteinas " << (*i).getProteinas() << "\tGrasas " << (*i).getGrasas();
			cout << "\tFibra " << (*i).getFibra() << endl << endl;
		}

		recetas pedidas(solucionGreedy(rall, MAX_CAL));

		if(!pedidas.empty()) {
			cout << "Las mejores recetas con Proteínas/Hidratos con menos de " << MAX_CAL << " son:" << endl;
			cout << pedidas << endl;
			
			double totalCal=0, totalPro=0;
			for (auto i = pedidas.begin(); i != pedidas.end(); ++i) {
				totalCal += (*i).getCalorias();
				totalPro += (*i).getProteinas();
			}

			cout << "Calorías Totales " << totalCal << " Proteínas Totales " << totalPro << endl;
		}
		else
			cout << "No se ha encontrado solución." << endl;

		return EXIT_SUCCESS;
	}
}
