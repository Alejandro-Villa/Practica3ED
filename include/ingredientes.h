#ifndef INGREDIENTES
#define INGREDIENTES

#include "VD.h"
#include "ingrediente.h"
#include <iostream>
#include <string>

class ingredientes {
	public:
		ingredientes();
		ingredientes(const ingredientes& original);
		//~ingredientes();
		
		void insertar(const ingrediente& nuevo);
		void borrar(std::string nombre);
		unsigned size() const;
		std::ostream& ImprimirPorTipo(std::ostream& out) const;
		ingrediente get(std::string nombre) const;
		VD<std::string> getTipos() const;
		ingredientes getIngredienteTipo(std::string tipo) const;

		friend std::ostream& operator<< (std::ostream& out, const ingredientes& is);
		friend std::istream& operator>> (std::istream& in, ingredientes& is);
	private:
		VD <ingrediente> datos;
		VD <int> indice;
		unsigned existe(const ingrediente& buscado, bool &encontrado) const;
		//void Ordena();
		//void OrdenaTipo();
		//void OrdenaNombre();
};

#endif
