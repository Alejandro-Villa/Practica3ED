#include <iostream>
#include "ingrediente.h"
#include "ingredientes.h"
#include <fstream>
#include <cmath>

using namespace std;

void MuestraParametros();
double media(const VD<double>& valores);
double desviacion(const VD<double>& valores);
VD<double> maximo(const VD<double>& valores);
VD<double> minimo(const VD<double>& valores);
VD<double> estadistica(const VD<double>& valores);

const unsigned NNUTRIENTES=5; // Número de macronutrientes.

int main(int argc, char *argv[]) {
	if (argc != 3) {
		MuestraParametros();
		return 1;
	}

	string archivo=argv[1];
	string tipo=argv[2];
	ifstream f(archivo);

	if(!f) {
		cerr << "ERROR: No se ha podido abrir el archivo" << endl;
		return 1;
	}

	ingredientes all_ingre;
	f >> all_ingre;

	VD<string> tipos_total=all_ingre.getTipos();

	cout << "Los tipos encontrados son: " << endl;
	for (unsigned i=0; i<tipos_total.size(); ++i)
		cout << tipos_total[i] << endl;
	
	ingredientes tipo_pedido(all_ingre.getIngredienteTipo(tipo));

	cout << endl << "Los ingredientes de tipo " << tipo << " son: " << endl;
	cout << tipo_pedido << endl;

	VD<VD<double>> macronutrientes;
	VD<VD<double>> medidas;
	macronutrientes.resize(NNUTRIENTES);
	medidas.resize(NNUTRIENTES);

	for (unsigned i=0; i < NNUTRIENTES; ++i) {
		macronutrientes[i].resize(tipo_pedido.size());
		for (unsigned j=0; j < macronutrientes[i].size(); ++j) {
			switch (i) {
				case 0:
					macronutrientes[i][j] = tipo_pedido[j].getCalorias();
					break;
				case 1:
					macronutrientes[i][j] = tipo_pedido[j].getHc();
					break;
				case 2:
					macronutrientes[i][j] = tipo_pedido[j].getProteinas();
					break;
				case 3:
					macronutrientes[i][j] = tipo_pedido[j].getGrasas();
					break;
				case 4:
					macronutrientes[i][j] = tipo_pedido[j].getFibra();
					break;
				default:
					cerr << "Switch por defecto, nutriente no reconocido" << endl;
			}
		}
	}
	
	for (unsigned i=0; i < medidas.size(); ++i)
		medidas[i]=estadistica(macronutrientes[i]);

	/** La matriz que queda es del tipo:
	 *
	 * | Índice | macronutriente		| 0: Media | 1: Desviación Típica | 2: Posición Máximo | 3: Máximo | 4: Posición Mínimo | 5: Mínimo |
	 * |:------:|:----------------------|:--------:|:--------------------:|:------------------:|:---------:|:------------------:|:---------:|
	 * | 0		| calorias				|		   |					  |					   |		   |					|			|
	 * | 1		| hidratos de carbono	|		   |					  |					   |		   |					|			|
	 * | 2		| proteinas				|		   |					  |					   |		   |					|			|
	 * | 3		| grasas				|		   |					  |					   |		   |					|			|
	 * | 4		| fibra					|		   |					  |					   |		   |					|			|
	 * --------------------------------------------------------------------------------------------------------------------------------------
	 *
	 *  Usamos esta información y le damos formato para sacarla por pantalla.
	 */

	string t="\t",pm="+-";

	cout << "Estadística ___________________________________" << endl;
	cout << "Tipo de Alimento " << tipo << endl;

	cout << endl << "Promedio +- Desviación" << endl;
	cout << "Calorías\tHidratos de Carb\tProteínas\tGrasas\tFibra" << endl;
	
	for (unsigned i=0; i < 5; ++i)
		cout << medidas[i][0] << pm << medidas[i][1] << t;
	cout << endl;

	cout << endl << "Máximos Valores" << endl;
	cout << "Calorías (Alimento)\tHidratos de Carb (Alimento)\tProteínas (Alimento)\tGrasas (Alimento)\tFibra (Alimento)" << endl;

	for (unsigned i=0; i < 5; ++i)
		cout << medidas[i][3] << " ("<< tipo_pedido[medidas[i][2]].getNombre() << ")" << t;
	cout << endl;

	cout << endl << "Mínimos Valores" << endl;
	cout << "Calorías (Alimento)\tHidratos de Carb (Alimento)\tProteínas (Alimento)\tGrasas (Alimento)\tFibra (Alimento)" << endl;

	for (unsigned i=0; i < 5; ++i)
		cout << medidas[i][5] << " (" << tipo_pedido[medidas[i][4]].getNombre() << ")" << t;
	cout << endl;

	return 0;
}

void MuestraParametros() {
	cout << "\tNúmero de parámetros incorrecto." << endl;
	cout << "\tUso correcto: " << endl;
	cout << "\t\t./tipos_ingredientes <fichero de datos> <tipo a procesar>" << endl;
}

double media(const VD<double>& valores) {
	double res=0;
	
	for (unsigned i=0; i < valores.size(); ++i)
		res+=valores[i];
	res /= (double)valores.size();
	
	return res;
}

double desviacion(const VD<double>& valores) {
	double m = media(valores);
	VD<double> dist(valores);
	
	for (unsigned i=0; i < dist.size(); ++i)
		dist[i] = (dist[i]-m)*(dist[i]-m);
	double var = media(dist);
	
	return sqrt(var);
}

VD<double> maximo(const VD<double>& valores) {
	double max=0;
	unsigned pmax=0;
	
	for (unsigned i=0; i < valores.size(); ++i) 
		if (valores[i] > max) {
			max = valores[i];
			pmax = i;
		}
	
	VD<double> res;
	res.add((double)pmax);
	res.add(max);
	
	return res;
}

VD<double> minimo(const VD<double>& valores) {
	double min;
	unsigned pmin;

	min = valores[1];
	for (unsigned i=0; i < valores.size(); ++i)
		if (valores[i] < min) {
			min = valores[i];
			pmin = i;
		}
	
	VD<double> res;
	res.add((double)pmin);
	res.add(min);
	
	return res;
}

VD<double> estadistica(const VD<double>& valores) {
	VD<double> resultado;

	resultado.resize(6);

	resultado[0]=media(valores);		// Media
	resultado[1]=desviacion(valores);	// Desviación Típica
	resultado[2]=maximo(valores)[0];	// Posicion del máximo
	resultado[3]=maximo(valores)[1];	// Valor del máximo
	resultado[4]=minimo(valores)[0];	// Posición del mínimo
	resultado[5]=minimo(valores)[1];	// Valor del mínimo

	return resultado;
}
