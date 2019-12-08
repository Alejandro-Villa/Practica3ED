#ifndef RECETA
#define RECETA

#include<string>
#include<list>
#include<iostream>

class receta {
	private:
		std::string code;
		unsigned plato;
		std::string nombre;
		std::list<std::pair<std::string, unsigned>> ings;
		float calorias, hc, grasas, proteinas, fibra;

	public:
		receta();
		receta(const receta& original);
		unsigned ningredientes() const;

		inline std::string getCode() const {return code;};
		inline unsigned getPlato() const {return plato;};
		inline std::string getNombre() const {return nombre;};
		inline float getCalorias() const {return calorias;};
		inline float getHc() const {return hc;};
		inline float getGrasas() const {return grasas;};
		inline float getProteinas() const {return proteinas;};
		inline float getFibra() const {return fibra;};


		void setCode(const std::string& codigo) {code = codigo;};
		void setPlato(const unsigned& pl) {plato = pl;};
		void setNombre(const std::string& name) {nombre = name;};
		void addIngre(const std::pair<std::string, unsigned>& nuevo) {ings.push_back(nuevo);};
		void setCalorias(const float& cal) {calorias = cal;};
		void setHc(const float& HC) {hc = HC;};
		void setGrasas(const float& gra) {grasas = gra;};
		void setProteinas(const float& prote) {proteinas = prote;};
		void setFibra(const float& fib) {fibra = fib;};

		friend std::istream& operator>>(std::istream& in, receta& r);
		friend std::ostream& operator<<(std::ostream& out, const receta& r);
		class iterator {
			private:
				std::list<std::pair<std::string, unsigned>>::iterator it;
			public:
				iterator() {};
				iterator(const std::list<std::pair<std::string, unsigned>>::iterator& origen) : it(origen) {};
				iterator(const receta::iterator& origen) : it(origen.it) {};
				iterator& operator++() {++it; return *this;};
				iterator& operator--() {--it; return *this;};
				bool operator==(const receta::iterator& rhs) const {return it == rhs.it;};
				bool operator!=(const receta::iterator& rhs) const {return it != rhs.it;};
				std::pair<std::string, unsigned>& operator*() const {return *it;};
				// iterator& operator+(const int& num) {it += num; return *this;};
				// int operator-(const receta::iterator& otro) { return it - otro.it; };
				inline const std::list<std::pair<std::string, unsigned>>::iterator getIterator() const {return it;};
		}; // end iterator
		class const_iterator {
			private:
				std::list<std::pair<std::string, unsigned>>::const_iterator it;
			public:
				const_iterator() {};
				const_iterator(const std::list<std::pair<std::string, unsigned>>::const_iterator& origen) : it(origen) {};
				const_iterator(const receta::const_iterator& origen) : it(origen.it) {};
				const_iterator& operator++() {++it; return *this;};
				const_iterator& operator--() {--it; return *this;};
				bool operator==(const receta::const_iterator& rhs) const {return it == rhs.it;};
				bool operator!=(const receta::const_iterator& rhs) const {return it != rhs.it;};
				const std::pair<std::string, unsigned>& operator*() const {return *it;};
				// const_iterator& operator+(const int& num) {it += num; return *this;};
				// int operator-(const receta::const_iterator& otro) { return it - otro.it; };
				inline const std::list<std::pair<std::string, unsigned>>::const_iterator getIterator() const {return it;};
		}; // end const_ iterator

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
}; // end receta
#endif
