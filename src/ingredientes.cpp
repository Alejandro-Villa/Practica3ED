#include "VD.h"
#include "ingredientes.h"
#include "ingrediente.h"
#include <iostream>
#include <string>

#define DEBUG false

using namespace std;

ingredientes::ingredientes() {
	// No es necesario, pues el constructor de VD ya asigna el puntero a nullptr. 
	// Lo hacemos aún así para asegurar consistencia.
	datos.resize(0);
	indice.resize(0);
}

ingredientes::ingredientes(const ingredientes& original) {
	// TO DO
}

unsigned ingredientes::size() const {
	return datos.size();
}

unsigned ingredientes::existeDatos(const ingrediente& buscado, bool &encontrado) const {
//	unsigned m=0, izq = 0, drcha = size()-1, pos=0;
	encontrado = false;

/*	BUSQUEDA BINARIA: FALLA */
/*
	if (size() > 0) {
 		if (buscado.getNombre() < datos[0].getNombre())
			pos = 0;
		else if (buscado.getNombre() > datos[drcha].getNombre())
			pos = drcha;
		else {
			m=(izq+drcha)/2;
			while (izq < drcha && !encontrado) {
				if (buscado.getNombre() > datos[m].getNombre())
					izq = m+1;
				else if (buscado.getNombre() < datos[m].getNombre())
					drcha = m-1;
				else if (buscado.getNombre() == datos[m].getNombre() && buscado.getTipo() == datos[m].getTipo()) {
					pos = m;
					encontrado = true;
				}
				m = (izq+drcha)/2;
			}
			while (!encontrado && datos[pos].getNombre() < buscado.getNombre()) {
				++pos;
			}
		}

	}
	else
		pos=0;
*/
/*
	// BUSQUEDA SECUENCIAL: FUNCIONA
	if(size() > 0) {
		while(pos < (unsigned)(size()-1) && datos[pos].getNombre() < buscado.getNombre())
			++pos;
		encontrado = ((datos[pos].getNombre() == buscado.getNombre()) && (datos[pos].getTipo() == buscado.getTipo()));
	}
*/

	// BUSQUEDA BINARIA: Segundo intento, códdigo de SO. FUNCIONA.
	unsigned lo=0, hi=(size()>0)?size()-1:0 ,mid=0;
	
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

	if(!esta) {
		datos.resize(size()+1);
		for (unsigned i = size()-1; i > dpos; --i)
			datos[i] = datos[i-1];
		datos[dpos] = nuevo;
		
		if(DEBUG)
			cout << "DEBUG: insertado en posicion " << dpos << endl;

		if(indice.size() > 0)
			for (unsigned i=0; i < indice.size(); ++i) 
				if (indice[i] >= dpos)
					++indice[i];
		unsigned ipos = existeIndice(nuevo);

		indice.resize(indice.size()+1);
		for (unsigned i=indice.size()-1; i > ipos; --i)
			indice[i] = indice[i-1];
		indice[ipos] = dpos;
	
		if(DEBUG)
			cout << "DEBUG: insertado indice en " << ipos << endl;
	}

//	int viejo_tam = size();
//
//	datos.resize(viejo_tam+1);
//	indice.resize(viejo_tam+1);
//	
//	datos[viejo_tam] = nuevo;
//
//	if(ordena) 
//		Ordena();
}

ostream& operator<< (ostream &out, const ingredientes &is) {
	for (int i = 0; i < is.datos.size(); ++i) {
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
//	is.Ordena();

	return in;
}

//void ingredientes::Ordena() {
//	// Ordenamos por nombre.
//	OrdenaNombre();
//	// y por tipo.
//	OrdenaTipo();
//}
//
//
//void ingredientes::OrdenaNombre() {
//	bool cambio = true;
//	for (unsigned i=0; i < (unsigned)(size()-1) && cambio; ++i) {
//		cambio=false;
//		for (unsigned j=0; j < (unsigned)(size()-i-1); ++j) {
//			if ((datos[j].getNombre().compare(datos[j+1].getNombre()))>0) {
//				cambio=true;
//				ingrediente aux(datos[j]);
//				datos[j] = datos[j+1];
//				datos[j+1] = aux;
//			}
//		}
//	}
//}
//
//void ingredientes::OrdenaTipo() {
//	bool encontrado = false;
//
//	for (unsigned i=0; i < size(); ++i) 
//		indice[i]=i;
//
//	for (unsigned i=0; i < size(); ++i) {
//		cambio=false;
//		for(unsigned j=0; j < size(); ++j) {
//			if()
//}

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
		if(datos[i].getTipo().compare(tipo) == 0)
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
		if(!repetido)
			totalTipos.add(tipo);
	}

	return totalTipos;
}

void ingredientes::borrar(string nombre) {
	ingrediente borrado(get(nombre));
	
	if (borrado.getNombre() != "Undefined") {
		bool encontrado = false;
		unsigned dpos = existeDatos(borrado, encontrado);
		
		if(DEBUG)
			cout << "DEBUG:Buscando índice" << endl;
		
		unsigned ipos = existeIndice(borrado);

		for (unsigned i=dpos; i < (unsigned)(size()-1); ++i) 
			datos[i] = datos[i+1];
		datos.resize(size()-1);
		
		for (unsigned i=ipos; i < indice.size()-1; ++i)
			indice[i]=indice[i+1];
		indice.resize(indice.size()-1);

		if(DEBUG)
			cout << "DEBUG:Decrementando indices" << endl;

		for (unsigned i=0; i < indice.size(); ++i)
			if (indice[i] >= dpos)
				--indice[i];
	}
	
/* IMPLEMENTACION ANTIGUA.
	bool encontrado = false;
	unsigned pos; 

	if(DEBUG)
		cout << "DEBUG:primer bucle" << endl;
	
	for (unsigned i=0; i < size() && !encontrado; ++i) {
		if(DEBUG)
			cout << "DEBUG: iteracion: " << i << endl;
		
		if(datos[i].getNombre().compare(nombre) == 0) {
			encontrado = true;
			pos = i;
			for (unsigned j = pos; j < (unsigned)(size()-1); ++j)
				datos[j] = datos[j+1];
			datos.resize(datos.size()-1);
		}
	}
	
	if(DEBUG)	
		cout << "DEBUG:segundo bucle" << endl;
	
	encontrado = false;
	for (unsigned i=0; i < indice.size() && !encontrado; ++i)
		if(indice[i] == pos) {
			encontrado = true;
			for (unsigned j = i; j < size(); ++j)
				indice[j] = indice[j+1];	
			indice.resize(indice.size()-1);
		}
*/
}
