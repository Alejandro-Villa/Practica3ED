#include<utility>
#include "recetas.h"

using namespace std;

recetas::recetas() {
	datos.clear();
}

unsigned recetas::size() const {
   return datos.size();
} 

void recetas::addReceta(const receta& nueva) {
		pair<string, receta> nelem = make_pair(nueva.getCode(), nueva);
		pair<map<string, receta>::iterator, bool> res;
		res	= datos.insert(nelem);
}

void recetas::borrar(string codigo) {
	unsigned borrados = datos.erase(codigo);
}

receta recetas::operator[](string codigo) {
	receta res;
	iterator ite(datos.find(codigo));
	
	if (ite != end())
		res = *ite;
	
	return res;
}

const receta recetas::operator[](string codigo) const {
	receta res;
	const_iterator ite(datos.find(codigo));
	
	if (ite != end())
		res = *ite;
	
	return res;
}
istream& operator>>(std::istream& in, recetas& rs) {
	while((!in.peek() != EOF) && (in.good())) {
		receta r;
		in >> r;
		rs.addReceta(r);
	}

	return in;
}

ostream& operator<<(std::ostream& out, const recetas& rs) {
	
	for(auto i = rs.begin(); i != rs.end(); ++i) {
		out << (*i).getCode() << ": " << (*i).getNombre() << endl; 
	}

	return out;
}

recetas::iterator recetas::begin() {
	iterator ite(datos.begin());
	return ite;
}

recetas::iterator recetas::end() {
	iterator ite(datos.end());
	return ite;
}

recetas::const_iterator recetas::begin() const {
	const_iterator ite(datos.cbegin());
	return ite;
}

recetas::const_iterator recetas::end() const {
	const_iterator ite(datos.cend());
	return ite;
}
