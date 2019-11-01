#include "VD.h"
#include "ingredientes.h"
#include "ingrediente.h"
#include <iostream>
#include <string>

#define DEBUG 0 /// Directiva de prepocesamiento para mensajes de depuración.

using namespace std;

ingredientes::ingredientes() {
	// No es necesario, pues el constructor de VD ya asigna el puntero a nullptr. 
	// Lo hacemos aún así para asegurar consistencia.
	datos.resize(0);
	indice.resize(0);
}

ingredientes::ingredientes(const ingredientes& original) {
	datos.resize(original.size());
	indice.resize(original.size());
	
	for (unsigned i=0; i < size(); ++i){
		datos[i] = original.datos[i];
		indice[i] = original.indice[i];
	}
}

unsigned ingredientes::size() const {
	return datos.size();
}

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
				if (datos[indice[mid]].getTipo() == buscado.getTipo() && datos[indice[mid]].getNombre() == buscado.getNombre()) {
					lo = mid;
					break;
				}
				else if (datos[mid].getNombre() > buscado.getNombre())
					hi = mid;
				else
					lo = mid + 1;
			}
			encontrado = (lo==mid)?true:(datos[lo-1].getNombre() == buscado.getNombre() && datos[lo-1].getTipo() == buscado.getTipo());
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
	if (indice.size() > 0) {
		if (buscado.getTipo() < datos[indice[0]].getTipo())
			lo=0;
		else if (buscado.getTipo() > datos[indice[indice.size()-1]].getTipo())
			lo=indice.size();
		else {
			while (lo < hi) {
				mid = (lo+hi)/2;
				if (datos[indice[mid]].getTipo() == buscado.getTipo() && datos[indice[mid]].getNombre() == buscado.getNombre()) {
					lo = mid;
					break;
				}
				else if (datos[indice[mid]].getTipo() > buscado.getTipo())
					hi = mid;
				else
					lo = mid + 1;
			}
		}
	}
		return lo;
}

void ingredientes::insertar(const ingrediente& nuevo) {
	bool esta = false;
	unsigned dpos = existeDatos(nuevo, esta);

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
}

ostream& operator<< (ostream &out, const ingredientes &is) {
	for (unsigned i = 0; i < is.datos.size(); ++i) {
		if(DEBUG)
			out << endl << "DEBUG:Ingrediente " << i << ":" << endl;
		out << is.datos[i];
	}
	return out;
}

istream& operator>> (istream &in, ingredientes &is) {
	ingrediente tmp;
	string linea;
	getline(in, linea);

	while (in >> tmp)
		is.insertar(tmp);

	return in;
}

ostream& ingredientes::ImprimirPorTipo(ostream& out) const {
	for (unsigned i=0; i < size(); ++i) {
		if(DEBUG)
			cout << endl << "DEBUG: Ingrediente " << i << ':' << endl;
		out << datos[indice[i]];
	}
	return out;
}

ingredientes ingredientes::getIngredienteTipo(string tipo) const {
	ingredientes resultado;

	for(unsigned i=0; i < size(); ++i)
		if(datos[i].getTipo() == tipo)
			resultado.insertar(datos[i]);

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

VD<string> ingredientes::getTipos() const {
	VD<string> totalTipos;
	
	for (unsigned i=0; i < size(); ++i) {
		string tipo = datos[i].getTipo();
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
			totalTipos.add(tipo);
		}
	}

	return totalTipos;
}

void ingredientes::borrar(string nombre) {
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
	}
}
