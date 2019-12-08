#ifndef RECETAS
#define RECETAS

#include "receta.h"
#include<string>
#include<map>
#include<utility>
#include<iostream>

class recetas {
	private:
		/*
		struct ComparaCode {
			bool operator() (const std::string& primer, const std::string& segundo) const {
				std::string comp1 = primer, comp2 = segundo;
				comp1.erase(0);
				comp2.erase(0);

				return std::stoi(comp1) < std::stoi(comp2);
			}
		}
		*/
		/*
		bool ComparaCode(const std::string& primer, const std::string& segundo) {
			std::string comp1 = primer, comp2 = segundo;
			comp1.erase(0);
			comp2.erase(0);

			return stoi(comp1) < stoi(comp2);
		}
		*/
		// std::map<std::string, receta, ComparaCode> datos;
		std::map<std::string, receta> datos;
	public:
			recetas();

			unsigned size() const;
			void borrar(std::string codigo);
			void addReceta(const receta& nueva);
	
			receta operator[](std::string codigo);
			const receta operator[](std::string codigo) const;

			friend std::istream& operator>>(std::istream& in, recetas& rs);
			friend std::ostream& operator<<(std::ostream& out, const recetas& rs);

			class iterator {
				private:
					std::map<std::string, receta>::iterator it;
				public:
					iterator() {};
					iterator(const std::map<std::string, receta>::iterator& origen) : it(origen) {};
					iterator(const recetas::iterator& origen) : it(origen.it) {};
					iterator& operator++() {++it; return *this;};
					iterator& operator--() {--it; return *this;};
					bool operator==(const recetas::iterator& rhs) const {return it == rhs.it;};
					bool operator!=(const recetas::iterator& rhs) const {return it != rhs.it;};
					receta& operator*() const {return (*it).second;};
					// inline const std::map<std::string, receta>::iterator getIterator() const {return it;};
			}; // end iterator
			class const_iterator {
				private:
					std::map<std::string, receta>::const_iterator it;
				public:
					const_iterator() {};
					const_iterator(const std::map<std::string, receta>::const_iterator& origen) : it(origen) {};
					const_iterator(const recetas::const_iterator& origen) : it(origen.it) {};
					const_iterator& operator++() {++it; return *this;};
					const_iterator& operator--() {--it; return *this;};
					bool operator==(const recetas::const_iterator& rhs) const {return it == rhs.it;};
					bool operator!=(const recetas::const_iterator& rhs) const {return it != rhs.it;};
					const receta& operator*() const {return (*it).second;};
					// inline const std::map<std::string, receta>::const_iterator getIterator() const {return it;};
			}; // end const_ iterator

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;


}; // end recetas

#endif
