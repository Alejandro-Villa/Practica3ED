#ifndef INGREDIENTE
#define INGREDIENTE

#include<string>
#include<iostream>

class ingrediente {
	public:
		inline std::string getNombre() const { return nombre; };
		inline std::string getTipo() const { return tipo; };
		inline double getCalorias() const { return calorias; };
		inline double getHc() const { return hc; };
		inline double getProteinas() const { return proteinas; };
		inline double getGrasas() const { return grasas; };
		inline double getFibra() const { return fibra; };

		ingrediente();
		ingrediente(const ingrediente & otro);

		ingrediente& operator= (const ingrediente& original);
		friend std::ostream &operator<<( std::ostream & out, const ingrediente & I);
		friend std::istream &operator>>( std::istream & in, ingrediente & I);
		
	private:
		std::string nombre;
		std::string tipo;
		double calorias;
		double hc;
		double proteinas;
		double grasas;
		double fibra;
};

#endif
