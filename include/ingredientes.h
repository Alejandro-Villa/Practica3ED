#ifndef INGREDIENTES
#define INGREDIENTES

#include "VD.h"
#include "ingrediente.h"
#include <iostream>
#include <string>
/**
 * @brief Clase que representa un conjunto de ingredientes.
 *
 * Esta clase representa un conjunto de ingredientes valiéndose de dos vectores dinámicos
 * de la clase @c VD. Los ingredientes se mantienen ordenados por nombre y por 
 * tipo, usando para la ordenación por tipo un vector de índices que apunta al vector de 
 * ingrediente. @see VD.h
 *
 */
class ingredientes {
	public:
		/**
		 * @brief Constructor por defecto.
		 *
		 * Para asegurarnos de que los vectores se han inicializado a cero, llamamos al 
		 * método @c VD::resize() con argumento @c 0.
		 */
		ingredientes();
		/**
		 * @brief Constructor de copia.
		 *
		 * Copia todos los elementos de @a original en ingredientes.
		 *
		 * @param "const ingredientes& original" Ingrediente que se copiará.
		 */
		ingredientes(const ingredientes& original);
		
		/**
		 * @brief Inserta un nuevo ingrediente.
		 *
		 * Este método inserta un nuevo ingrediente en el vector dinámico, de forma que 
		 * se mantenga la ordenación del vector por nombre y también por tipo. 
		 *
		 * @pre Si @a nuevo ya está incluido, no se vuelve a insertar.
		 * @param "" Ingrediente a insertar
		 * @post El vector @a datos e @a indice incluyen ahora el nuevo elemento y su
		 * índice, respectivamente.
		 */
		void insertar(const ingrediente& nuevo);
		/**
		 * @brief Borra un ingrediente representado por @a nombre.
		 *
		 * Este método busca el ingrediente cuyo nombre sea @a nombre, valiéndose para 
		 * ello de @c ingredientes::get(), luego lo borra y realiza los ajustes necesarios
		 * en los dos vectores.
		 *
		 * @pre si @a nuevo no existe, no ocurre nada.
		 * @post @a nuevo es borrado del vector, en el caso de repetición, se borra su 
		 * primera ocurrencia.
		 */
		void borrar(std::string nombre);
		/**
		 * @brief Devuelve la cantidad de ingredientes.
		 *
		 * Este método es una llamada a @c datos.size() (método @c VD::size()) que nos 
		 * devuelve el tamaño de @a datos. Dado que siempre @a datos e @a indice son del 
		 * mismo tamaño, este valor es el número efectivo de ingredientes que contiene el
		 * vector.
		 *
		 * @retval unsigned Número de ingredientes.
		 */
		unsigned size() const;
		/**
		 *
		 */
		std::ostream& ImprimirPorTipo(std::ostream& out) const;
		ingrediente get(std::string nombre) const;
		VD<std::string> getTipos() const;
		ingredientes getIngredienteTipo(std::string tipo) const;
		inline const ingrediente& operator[](const unsigned pos) const {return datos[pos];};
		inline ingrediente& operator[](const unsigned pos) {return datos[pos];};


		friend std::ostream& operator<< (std::ostream& out, const ingredientes& is);
		friend std::istream& operator>> (std::istream& in, ingredientes& is);
	private:
		VD <ingrediente> datos;
		VD <int> indice;
		unsigned existeDatos(const ingrediente& buscado, bool &encontrado) const;
		unsigned existeIndice(const ingrediente& buscado) const;
};

#endif
