/* 
 * @file ingrediente.cpp
 * @brief Implementación de la clase ingrediente.
 */

#include "ingrediente.h"
#include<iostream>
#include<string>

using namespace std;

ingrediente::ingrediente() {
	nombre="Undefined";
	tipo="Undefined";
	calorias=-1;
	hc=-1;
	proteinas=-1;
	grasas=-1;
	fibra=-1;
}

ingrediente::ingrediente(const ingrediente& otro) {
	nombre=otro.getNombre();
	tipo=otro.getTipo();
	calorias=otro.getCalorias();
	hc=otro.getHc();
	proteinas=otro.getProteinas();
	grasas=otro.getGrasas();
	fibra=otro.getFibra();
}

ostream &operator<<( ostream &out, const ingrediente& I) {
	char pc = ';';
	out << I.getNombre() << pc << I.getCalorias() << pc << I.getHc() << pc << I.getProteinas() << pc << I.getGrasas() << pc << I.getFibra() << pc << I.getTipo() << endl;

	return out;
}

istream &operator>>( istream &in, ingrediente& I) {
	string tmp;

	getline(in ,tmp, ';');
	I.nombre=tmp;
	getline(in ,tmp, ';');
	I.calorias=atof(tmp.c_str());
	getline(in ,tmp, ';');
	I.hc=atof(tmp.c_str());
	getline(in ,tmp, ';');
	I.proteinas=atof(tmp.c_str());
	getline(in ,tmp, ';');
	I.grasas=atof(tmp.c_str());
	getline(in ,tmp, ';');
	I.fibra=atof(tmp.c_str());
	getline(in ,tmp);
	I.tipo=tmp;

	return in;
}

ingrediente& ingrediente::operator= (const ingrediente& original) {
	nombre = original.getNombre();
	tipo = original.getTipo();
	calorias = original.getCalorias();
	hc = original.getHc();
	proteinas = original.getProteinas();
	grasas = original.getGrasas();
	fibra = original.getFibra();

	return *this;
}
