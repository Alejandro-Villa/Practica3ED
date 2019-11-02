#ifndef VDinclude
#define VDinclude

#include<iostream>

template <class T>
class VD {
	private:
		/**
		 * @brief Vector que almacena los datos.
		 *
		 * Este puntero apuntará a un vector dinámico que almacenará los datos que se
		 * manejen en la clase.
		 */
		T* datos;
		/**
		 * @brief Tamaño de @a datos.
		 *
		 * Este entero almacena el número total de elementos del vector.
		 */
		int nelementos;
	public:
		/**
		 * @brief Constructor por defecto y parametrizado con númmero de elementos. 
		 *
		 * Este constructor inicializa el vector @a datos y @a nelementos con 
		 * @a n número de elementos, haciendo la reserva de memoria pertinnente.
		 *
		 * @param "int n=0" Número de elementos del vector, en caso de no proporcionarse
		 * argumento, se inicializa a 0 (@c nullptr).
		 * @precond @a n debe ser positivo.
		 */
		VD(int n=0);
		/**
		 * @brief Constructor de copia.
		 *
		 * Copia todos los elementos de @a original en @a this. Reserva memoria
		 * adecuadamente.
		 */
		VD(const VD& original);
		~VD();

		unsigned size() const;
		T& operator[](int i);
		const T& operator[](int i) const;
		void add(T nuevo);
		void resize(int n);
		VD<T>& operator= (const VD<T>& original);
};

#include "VD.cpp"

#endif
