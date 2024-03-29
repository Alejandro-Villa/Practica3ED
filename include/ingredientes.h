/**
 * @file ingredientes.h
 *
 * @brief Archivo cabecera de la clase @c ingredientes::ingredientes
 */

#ifndef INGREDIENTES
#define INGREDIENTES

#include "ingrediente.h"
#include <iostream>
#include <string>
#include <vector>
/**
 * @brief Clase que representa un conjunto de ingredientes.
 *
 * Esta clase representa un conjunto de ingredientes valiéndose de dos vectores dinámicos
 * de la clase @c vector. Los ingredientes se mantienen ordenados por nombre y por 
 * tipo, usando para la ordenación por tipo un vector de índices que apunta al vector de 
 * ingrediente. @see vector
 */
class ingredientes {
	public:
		/**
		 * @brief Constructor por defecto.
		 *
		 * Utiliza los constructores que provee @c vector para inicializar los datos miembro.
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
		 * @post El vector @a datos e @a indice incluyen ahora el nuevo elemento y su
		 * índice, respectivamente.
		 * @param "const ingrediente& nuevo" Ingrediente a insertar
		 */
		void insertar(const ingrediente& nuevo);
		/**
		 * @brief Borra un ingrediente representado por @a nombre.
		 *
		 * Este método busca el ingrediente cuyo nombre sea @a nombre, valiéndose para 
		 * ello de @c ingredientes::get(), luego lo borra y realiza los ajustes necesarios
		 * en los dos vectores.
		 *
		 * @pre si @a nombre no existe, no ocurre nada.
		 * @post @a nombre es borrado del vector, en el caso de repetición, se borra su 
		 * primera ocurrencia.
		 * @param "std::string nombre" El nombre del ingrediente a borrar.
		 */
		void borrar(std::string nombre);
		/**
		 * @brief Devuelve la cantidad de ingredientes.
		 *
		 * Este método es una llamada a @c datos.size() (método @c vector::size()) que nos 
		 * devuelve el tamaño de @a datos. Dado que siempre @a datos e @a indice son del 
		 * mismo tamaño, este valor es el número efectivo de ingredientes que contiene el
		 * vector.
		 *
		 * @retval unsigned Número de ingredientes.
		 */
		unsigned size() const;
		/**
		 * @brief Imprime los ingredientes por orden alfabético de tipo.
		 *
		 * Este método imprime por el buffer @a out los ingredientes en orden alfabético
		 * descendente según su tipo. 
		 * Si existiese igualdad de tipo, se usaría el nombre.
		 *
		 * @param "std::ostream& out" El buffer por el que se dará salida a los datos.
		 * @retval "std::ostream&" El mismo buffer @a out.  
		 */
		std::ostream& ImprimirPorTipo(std::ostream& out) const;
		/**
		 * @brief Devuelve el ingrediente @a nombre.
		 *
		 * Este método busca y devuelve el ingrediente cuyo nombre coincida con el
		 * argumento dado. En caso de que no se encuentre, devuelve @c "Undefined", un
		 * objeto @a ingrediente creado por el constructor sin parámetros. 
		 *
		 * @param "std::string nombre" El nombre del ingrediente que se buscará. En caso
		 * de repetición se devuelve la primera ocurrencia.
		 * @retval ingrediente El ingrediente encontrado, o uno inicializado por defecto
		 * si no se encuentra.
		 */
		ingrediente get(std::string nombre) const;
		/**
		 * @brief Devuelve todos los tipos de ingredientes.
		 *
		 * Este método devuelve todos los tipos de ingredientes que existen en el objeto
		 * en el momento de llamar al método. Los devuelve en un objeto de tipo @c vector
		 *
		 * @retval "vector<std::string>" Vector dinámico conteniendo todos los tipos, sin 
		 * repetirse ninguno, en orden alfabético. De no haber ningún tipo devuelve un 
		 * vector vacío.
		 */
		std::vector<std::string> getTipos() const;
		/**
		 * @brief Devuelve todos los ingredientes del mismo tipo.
		 *
		 * Este método devuelve un objeto de tipo @c ingredientes que contiene todos los
		 * ingredientes de tipo @a tipo. En caso de no haber ninguno, devuelve un objeto 
		 * vacío (inicializado por defecto).
		 *
		 * @param "std::string tipo" El tipo de los ingredientes que se devolverán.
		 * @retval "ingredientes" Todos los ingredientes son de tipo @a tipo.
		 */
		ingredientes getIngredienteTipo(std::string tipo) const;
		/**
		 * @brief Clase Iterador.
		 *
		 * Esta clase implementa un iterador para ingredientes, 
		 * usando como base el iterator de la clase STL vector. 
		 * Concretamente usa el iterator de datos.
		 */
		class iterator {
			private:
				/**
				 * @brief Iterator de la Standard Template Library.
				 */
				std::vector<ingrediente>::iterator it;
			public:
				/**
				 * @brief Constructor por defecto.
				 *
				 * Inicializa @a ita @a datos.begin()
				 */
				iterator() {};
				/**
				 * @brief Constructor de iterador.
				 *
				 * Este constructor toma como parámetro un iterador de STL vector.
				 *
				 * @param "const std::vector<ingredientes>::iterator& origen" El iterador que va a copiarse en @a it
				 * @post Ahora @a it está inicializado.
				 */
				iterator(const std::vector<ingrediente>::iterator& origen) : it(origen) {};
				/**
				 * @brief Constructor de copia.
				 *
				 * Toma como parámetro otro objeto de iterador y lo copia en @a this.
				 *
				 * @param "const ingredientes::iterator& origen" El objeto que se copiará.
				 * @post @a this y @a origen son iguales.
				 */
				iterator(const ingredientes::iterator& origen) : it(origen.it) {};
				/**
				 * @brief Operador de pre-incremento.
				 *
				 * Este operador incrementa el iterador para que apunte al siguiente elemento de @a datos.
				 *
				 * @post @a it ahora apunta a la siguiente posición de @a datos.
				 * @retval iterator& referencia a @a this.
				 */
				iterator& operator++() {++it; return *this;};
				/**
				 * @brief Operador de decremento.
				 *
				 * Este operador decrementa el iterador para que apunte al anterior elemento de @a datos.
				 *
				 * @post @a it ahora apunta a la anterior posición de @a datos.
				 * @retval iterator& referencia a @a this.
				 */
				iterator& operator--() {--it; return *this;};
				/**
				 * @brief operador de comparación booleana (igualdad)
				 *
				 * Este operador compara si @a this y @a rhs apuntan al mismo elemento.
				 * Devuelve @a True si es así, @a False en otro caso.
				 *
				 * @param "const ingredientes::iterator& rhs" El iterador con el que vamos a comparar. 
				 * @retval bool @a True si son iguales, @a False en otro caso.
				 */
				bool operator==(const ingredientes::iterator& rhs) const {return it == rhs.it;};
				/**
				 * @brief operador de comparación booleana (desigualdad)
				 *
				 * Este operador compara si @a this y @a rhs apuntan a distinto elemento.
				 * Devuelve @a True si es así, @a False en otro caso.
				 *
				 * @param "const ingredientes::iterator& rhs" El iterador con el que vamos a comparar. 
				 * @retval bool @a True si son distintos, @a False en otro caso.
				 */
				bool operator!=(const ingredientes::iterator& rhs) const {return it != rhs.it;};
				/**
				 * @brief Operador de acceso.
				 *
				 * Devuelve el elemento al que apunta @a it.
				 *
				 * @retval ingrediente& El elemento de @a datos al que apunta @it.
				 * @post No se altera @a it ni @a datos.
				 */
				ingrediente& operator*() const {return *it;};
				/**
				 * @brief Operador de suma con enteros.
				 *
				 * Hace que el iterador apunte @a num posiciones adelante.
				 *
				 * @param "const int& num" Número de posiciones a adelantar.
				 * @retval iterator& el iterador modificado.
				 */ 
				iterator& operator+(const int& num) {it += num; return *this;};
				/**
				 * @brief Operador de distancia.
				 *
				 * Devuelve la distancia entre dos objetos de @a iterator.
				 *
				 * @param "const ingredientes::iterator& otro" otro iterator para calcular la distancia.
				 * @retval int La distancia entre los iteradores
				 */
				int operator-(const ingredientes::iterator& otro) { return it - otro.it; };
				/**
				 * @brief Getter de @a it.
				 *
				 * @retval "const std::vector<ingrediente>::iterator" Devuelve @a it.
				 */
				inline const std::vector<ingrediente>::iterator getIterator() const {return it;};

		};
		class const_iterator {
			private:
				std::vector<ingrediente>::const_iterator it;
			public:
				const_iterator(const std::vector<ingrediente>::const_iterator& origen) : it(origen) {};
				const_iterator(const ingredientes::const_iterator& origen) : it(origen.it) {};
				const_iterator& operator++() {++it; return *this;};
				const_iterator& operator--() {--it; return *this;};
				bool operator==(const ingredientes::const_iterator& rhs) const {return it == rhs.it;};
				bool operator!=(const ingredientes::const_iterator& rhs) const {return it != rhs.it;};
				const ingrediente& operator*() {return *it;};
				inline const std::vector<ingrediente>::const_iterator getIterator() const {return it;};
		};

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		/**
		 * @brief operador[] constante.
		 *
		 * Este método devuelve el ingrediente en la posición @a pos, en el vector 
		 * @a datos. En caso de ser un índice inválido aborta el programa. El método 
		 * está implementado como inline para mejorar el rendimiento, ya que se prevee 
		 * que será llamado muchas veces.
		 *
		 * @pre @a pos debe ser un índice válido, esto es, positivo y menor que 
		 * @c size().
		 * @param "unsigned pos" La posición a la que se va a acceder.
		 * @retval "const ingrediente& " Ingrediente en la posición @a pos.
		 */
		inline const ingrediente& operator[](const unsigned pos) const {return datos[pos];};
		/**
		 * @brief operador[] no constante.
		 *
		 * Exactamente la misma implementación que @c ingredientes::operator[].
		 *
		 * @see ingredientes::operator[]
		 */
		inline ingrediente& operator[](const unsigned pos) {return datos[pos];};

		/**
		 * @brief Sobrecarga del operador de salida de flujo.
		 *
		 * Este operador sobrecargado envía al buffer @a out el objeto @a is que se le 
		 * pase como parámetro. Lo hace valiéndose de @c ingrediente::operator<<. 
		 *
		 * Se implementa recorriendo el vector datos y enviando al flujo cada elemento.
		 * Por lo tanto son enviados por orden alfabético de nombre.
		 *
		 * @param "std::ostream& out" Flujo de salida de datos por dónde se enviará 
		 * @a is.
		 * @param "const ingredientes& is" Objeto de la clase que se enviará por @a out.
		 *
		 * @retval "std::ostream&" El flujo de salida tras el envío de datos.
		 */
		friend std::ostream& operator<< (std::ostream& out, const ingredientes& is);
		/**
		 * @brief Sobrecarga del operador de entrada de flujo.
		 *
		 * Este operador sobrecargado va leyendo ingredientes del flujo según la siguiente
		 * convención:
		 *
		 * 1. Se descarta la primera línea (hasta @c "\n"), considerada marca de formato.
		 * 2. Se comprueba si se ha alcanzado el fin del flujo. (@c std::EOF).
		 * 3. Se lee un ingrediente con @c ingrediente::operator>>.
		 * 4. Se inserta el ingrediente con @c insertar().
		 * 5. Se vuelve al paso 2.
		 *
		 * Una vez concluido el proceso, toda la información se debe encontrar en el
		 * objeto ingredientes @a is.
		 *
		 * @param "std::istream& in" Flujo de entrada.
		 * @param "ingredientes& is" Objeto donde se almacenará la información.
		 *
		 * @retval "std::istream&" El Flujo de entrada tras la operación.
		 * 
		 */
		friend std::istream& operator>> (std::istream& in, ingredientes& is);
		friend bool comparaNombre(const ingrediente& primero, const ingrediente& segundo);
		//friend bool comparaTipo(const ingrediente& primero, const ingrediente& segundo);
	private:
		/**
		 * @brief Vector que almacena los ingredientes.
		 *
		 * Este vector almacena todos los objetos @a ingrediente que la clase maneja en 
		 * cada momento. Es un vector dinámico. 
		 *
		 * Los ingredientes que contiene se encuentran ordenados por orden alfabético de
		 * nombre, y se mantienen así en todo momento.
		 */
		std::vector<ingrediente> datos;
		/**
		 * @brief Vector auxiliar de índices.
		 *
		 * Este vector contiene enteros que apuntan a posiciones de @a datos. El motivo de
		 * este vector es mantener la ordenación por tipo. El vector se encuentra ordenado
		 * de tal forma que al recorrer las posiciones de @a datos a las que apunta 
		 * @a indice, se obtiene la ordenación Alfabética por Tipo, y a igualdad de tipo,
		 * por nombre.
		 */
		std::vector<int> indice;
		/**
		 * @brief Método para hallar la posición de un ingrediente en @a datos.
		 *
		 * Este método busca, empleando el algoritmo de búsqueda binaria, un ingrediente 
		 * en el vector @a datos, en el caso de que no se encuentre, devuelve la posición
		 * dónde debería estar según orden alfabético de nombres. La información sobre si 
		 * ha sido encontrado o no se registra en la variable @a encontrado.
		 *
		 * @param "const ingrediente& buscado" El ingrediente que se buscará.
		 * @param "bool &encontrado" La variable que indica si se ha encontrado.
		 * @post @a encontrado será @c true si se ha encontrado el ingrediente, de lo contrario
		 * será @c false.
		 * @retval unsigned Posición del ingrediente, o la que debería tener. 
		 */
		//unsigned existeDatos(const ingrediente& buscado, bool &encontrado) const;
		iterator existeDatos(const ingrediente& buscado, bool &encontrado) const;
		/**
		 * @brief Método para hallar la posición de un ingrediente en @a indice.
		 *
		 * Este método busca, empleando el algoritmo de búsqueda binaria, la posición de 
		 * un ingrediente en @a indice, o de no encontrarse, la posición donde estaría 
		 * atendiendo al orden alfabético de tipo, o a igualdad de tipo, atendiendo al 
		 * nombre. No se devuelve información sobre si el elemento se encontró, pues
		 * para ello se emplea el método @c existeDatos() o @c get().
		 *
		 * @param "const ingrediente& buscado" Ingrediente a encontrar.
		 * @retval unsigned Posición donde se encuentra o donde debería.
		 */
		//unsigned existeIndice(const ingrediente& buscado) const;
		iterator existeIndice(const ingrediente& buscado) const;
};

#endif
