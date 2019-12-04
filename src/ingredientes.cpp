/**
 * @file ingredientes.cpp
 * @brief Implementación de la clase @c ingredientes::ingredientes.
 */
#include "ingredientes.h"
#include "ingrediente.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/**
 * @brief Directiva de preprocesamiento para depuración.
 *
 * Si esta macro está definida a @c 1 o @c true, se mostrarán mensajes de depuración por salida estándar.
 *
 * Si está definida a @c 0 o @c false, no se mostrarán mensajes.
 */
#define DEBUG 0

using namespace std;

ingredientes::iterator ingredientes::begin() {
	return ingredientes::iterator(datos.begin());
}

ingredientes::iterator ingredientes::end() {
	return ingredientes::iterator(datos.end());
}

ingredientes::const_iterator ingredientes::begin() const {
	return ingredientes::const_iterator(datos.cbegin());
}

ingredientes::const_iterator ingredientes::end() const {
	return ingredientes::const_iterator(datos.cend());
}

ingredientes::ingredientes() {
	// No es necesario, pues el constructor de vector ya asigna el puntero a nullptr. 
}

ingredientes::ingredientes(const ingredientes& original) {
	datos = original.datos;
	indice = original.indice;	
	/*	
	for (unsigned i=0; i < size(); ++i){
		datos[i] = original.datos[i];
		indice[i] = original.indice[i];
	}
	*/
}

unsigned ingredientes::size() const {
	return datos.size();
}
ingredientes::iterator ingredientes::existeDatos(const ingrediente& buscado, bool &encontrado) const {
	encontrado = false;

}

bool comparaNombre(const ingrediente& primero, const ingrediente& segundo) {
	return primero.getNombre() < segundo.getNombre();
}

void ingredientes::insertar(const ingrediente& nuevo) {
	if(size() > 0) {
		if (nuevo.getNombre() > datos.back().getNombre()) {
			datos.push_back(nuevo);
			indice.push_back(indice.size());
		}
		else {
		iterator pos(lower_bound(datos.begin(), datos.end(), nuevo, comparaNombre));
	
		if( !((*pos).getNombre() == nuevo.getNombre()) ) {
			int posicion = pos - begin();
			for(auto it = indice.begin(); it != indice.end(); ++it)
				if(*it >= posicion)
					++(*it);

			datos.insert(pos.getIterator(), nuevo);

            auto comparaTipo = [&](int uno, const ingrediente& otro) {
				if(datos[uno].getTipo() < otro.getTipo())
					return true;
				else if (datos[uno].getTipo() == otro.getTipo())
					return datos[uno].getNombre() < otro.getNombre();
				else
					return false;
			};

			vector<int>::iterator indicepos = lower_bound(indice.begin(), indice.end(), nuevo, comparaTipo);
			indice.insert(indicepos, posicion);
			}
		}
	}
	else { 
		datos.push_back(nuevo);
		indice.push_back(0);
	}
}
/*
unsigned ingredientes::existeDatos(const ingrediente& buscado, bool &encontrado) const {
	encontrado = false;
	unsigned lo=0, hi=(size()>0)?size()-1:0 ,mid=0;
	
	// Búsqueda binaria. Devuelve la mejor aproximación en el caso de que el elemento no exista.
	if (size() > 0) {
		if (buscado.getNombre() <= datos[0].getNombre())
			lo=0;
		else if (buscado.getNombre() >= datos[size()-1].getNombre())
			lo=size();
		else {
			while (lo < hi) {
				mid = (lo+hi)/2;
				if (datos[mid].getTipo() == buscado.getTipo() && datos[mid].getNombre() == buscado.getNombre()) {
					encontrado = true;
					lo = mid;
					break;
				}
				else if (datos[mid].getNombre() > buscado.getNombre())
					hi = mid;
				else
					lo = mid + 1;
			}
		}
	}
	else
		lo=0;

	if(DEBUG)
		cout << "DEBUG: encontrado: " << encontrado << "\tPosición: " << lo << endl;

	return lo;
}

unsigned ingredientes::existeIndice(const ingrediente& buscado) const {
	unsigned lo=0, hi=(indice.size()>0)?(indice.size()-1):0, mid=0;

	// Búsqueda binaria con mejor aproximación.
	// Comprobamos que el tamaño es positivo.
	if (indice.size() > 0) { 
		// Comprobamos si el nuevo elemento se sale de los límites por abajo (menor que todo el vector.
		if ( (buscado.getTipo() < datos[indice[0]].getTipo()) || (buscado.getTipo() == datos[indice[0]].getTipo() && buscado.getNombre() < datos[indice[0]].getNombre()) ) 
			lo=0;
		// Ídem pero si el elemento es mayor que todo el vector
		else if ( (buscado.getTipo() > datos[indice[indice.size()-1]].getTipo()) || (buscado.getTipo() == datos[indice[indice.size()-1]].getTipo() && buscado.getNombre() > datos[indice[indice.size()-1]].getNombre()) ) 
			lo=indice.size();
		// En este caso el elemento debe insertarse en algún punto intermedio del vector. Usamos búsqueda binaria.
		else { 
			while (lo < hi) { 
				mid = (lo+hi)/2;
				// El elemento ha sido encontrado.
				if (datos[indice[mid]].getTipo() == buscado.getTipo() && datos[indice[mid]].getNombre() == buscado.getNombre()) { 
					lo = mid;
					break; // Finalizamos el bucle.
				}
				// El elemento está en la mitad inferior del vector.
				else if ( (datos[indice[mid]].getTipo() > buscado.getTipo()) || (datos[indice[mid]].getTipo() == buscado.getTipo() && datos[indice[mid]].getNombre() > buscado.getNombre()) ) 
					hi = mid;
				// El elemento está en la mitad superior del vector.
				else 
					lo = mid + 1;
			}
		}
	}
		return lo; // Devolvemos la posición donde lo encontramos.
}
*//*
void ingredientes::insertar(const ingrediente& nuevo) {
	bool esta = false;
	unsigned dpos = existeDatos(nuevo, esta);

	if(DEBUG)
		cout << "DEBUG:insertando: " << nuevo << endl;
	// Si el ingrediente ya existe no insertamos nada.
	if(!esta) {
		datos.resize(size()+1);
		for (unsigned i = size()-1; i > dpos; --i)
			datos[i] = datos[i-1];
		datos[dpos] = nuevo;
		
		if(DEBUG)
			cout << "DEBUG: insertado en posicion " << dpos << endl;

		if(indice.size() > 0)
			for (unsigned i=0; i < indice.size(); ++i) 
				if ((unsigned)indice[i] >= dpos)
					++indice[i];
		unsigned ipos = existeIndice(nuevo);

		indice.resize(indice.size()+1);
		for (unsigned i=indice.size()-1; i > ipos; --i)
			indice[i] = indice[i-1];
		indice[ipos] = dpos;
	
		if(DEBUG)
			cout << "DEBUG: insertado indice en " << ipos << endl;
	}
	else 
		cout << "Ya está" << endl;
}
*/
ostream& operator<< (ostream &out, const ingredientes &is) {
	for (auto i = is.begin(); i != is.end(); ++i) 
		out << *i;
	/*
	for (unsigned i = 0; i < is.datos.size(); ++i) {
		if(DEBUG)
			out << endl << "DEBUG:Ingrediente " << i << ":" << endl;
		out << is.datos[i];
	}
	*/
	return out;
}

istream& operator>> (istream &in, ingredientes &is) {
	ingrediente tmp;
	string linea;
	getline(in, linea);

	unsigned i=0;

	while (in.peek() != EOF && in.good()) {
		in >> tmp;
		if(DEBUG) {
			cout << "DEBUG:Ingrediente a insertar " << tmp << endl;
		}
		++i;
		is.insertar(tmp);
	}

	if(DEBUG)
		cout << "DEBUG: Total insertados: " << i << endl;

	return in;
}

ostream& ingredientes::ImprimirPorTipo(ostream& out) const {
	for (auto i=indice.begin(); i != indice.end(); ++i) {
		out << datos[*i];
	}
	return out;
}

ingredientes ingredientes::getIngredienteTipo(string tipo) const {
	ingredientes resultado;

	for (auto i = begin(); i != end(); ++i) {
		if((*i).getTipo() == tipo)
			resultado.insertar((*i));
	}
	/*
	for(unsigned i=0; i < size(); ++i)
		if(datos[i].getTipo() == tipo)
			resultado.insertar(datos[i]);
	*/
	return resultado;
}

ingrediente ingredientes::get(string nombre) const {
	ingrediente resultado;
	bool encontrado = false;

	for (unsigned i=0; i < size() && !encontrado; ++i)
		if (datos[i].getNombre() == nombre) {
			encontrado = true;
			resultado = datos[i];
			if(DEBUG)
				cout << "DEBUG:indice: " << i << endl;
		}

	return resultado;
}

vector<string> ingredientes::getTipos() const {
	vector<string> totalTipos;
	
	for (auto i = indice.begin(); i != indice.end(); ++i) {
		string tipo = datos[(*i)].getTipo();
		bool repetido = false;
		for (auto j = totalTipos.begin(); j != totalTipos.end(); ++j)
			if(*j == tipo) {
				repetido = true;
				break;
			}
		if(!repetido)
			totalTipos.push_back(tipo);
	}
	/*
	for (unsigned i=0; i < size(); ++i) {
		string tipo = datos[indice[i]].getTipo();
		unsigned j = 0;
		bool repetido = false;
		while(j < totalTipos.size() && !repetido) { 
			if(totalTipos[j] == tipo)
				repetido = true;
			++j;
		}
		if(!repetido) {
			if(DEBUG)
				cout << "DEBUG:Añadiendo tipo " << tipo << endl;
			totalTipos.push_back(tipo);
		}
	}
*/
	return totalTipos;
}

void ingredientes::borrar(string nombre) {
	/*
	ingrediente borrado(get(nombre));
	
	if (borrado.getNombre() != "Undefined") {
		bool encontrado = false;
		unsigned dpos = existeDatos(borrado, encontrado); // Usamos los mismos métodos de búsqueda que para insertar.
		
		if(DEBUG)
			cout << "DEBUG:Buscando índice" << endl;
		
		unsigned ipos = existeIndice(borrado); // Mismo método que para insertar.

		for (unsigned i=dpos; i < (unsigned)(size()-1); ++i) 
			datos[i] = datos[i+1];
		datos.resize(size()-1);
		
		for (unsigned i=ipos; i < indice.size()-1; ++i)
			indice[i]=indice[i+1];
		indice.resize(indice.size()-1);

		if(DEBUG)
			cout << "DEBUG:Decrementando indices" << endl;
		
		// Necesitamos decrementar el índice para que se adapte al cambio de tamaño en datos.
		for (unsigned i=0; i < indice.size(); ++i)
			if ((unsigned)indice[i] >= dpos)
				--indice[i];
	}*/
}
