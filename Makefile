# MAKEFILE.
# Autor: Alejandro Villanueva Prados.
# Modificada de un Makefile anterior entregado por el profesor de prácticas F. David Charte Luque.

SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
WARN = -Wall -Wpedantic -Wextra # Añadir si se quieren warnings detalladas
								# Nota: una de ellas salta en test_ingredientes debido a mi elección de valores de retorno del metodo size().
CPPFLAGS = -g -I$(INC) -c --std=c++11 
all:$(BIN)/test_ingredientes $(BIN)/test_receta $(BIN)/nutricion_receta

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile
	
# ************ Compilación de módulos ************

$(BIN)/test_ingredientes: $(OBJ)/test_ingredientes.o $(OBJ)/ingredientes.o $(OBJ)/ingrediente.o
	$(CXX) -o $(BIN)/test_ingredientes $(OBJ)/test_ingredientes.o $(OBJ)/ingredientes.o $(OBJ)/ingrediente.o 

$(BIN)/test_receta: $(OBJ)/test_receta.o $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o $(OBJ)/receta.o $(OBJ)/recetas.o
	$(CXX) -o $(BIN)/test_receta $(OBJ)/test_receta.o $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o $(OBJ)/receta.o $(OBJ)/recetas.o

$(BIN)/nutricion_receta: $(OBJ)/nutricion_receta.o $(OBJ)/receta.o $(OBJ)/recetas.o $(OBJ)/ingredientes.o $(OBJ)/ingrediente.o
	$(CXX) -o $(BIN)/nutricion_receta $(OBJ)/nutricion_receta.o $(OBJ)/receta.o $(OBJ)/recetas.o $(OBJ)/ingredientes.o $(OBJ)/ingrediente.o

$(OBJ)/test_ingredientes.o: $(SRC)/test_ingredientes.cpp $(INC)/ingrediente.h $(INC)/ingredientes.h
	$(CXX) $(CPPFLAGS) $(SRC)/test_ingredientes.cpp -o $(OBJ)/test_ingredientes.o 

$(OBJ)/test_receta.o: $(SRC)/test_receta.cpp $(INC)/ingrediente.h $(INC)/ingredientes.h $(INC)/receta.h $(INC)/recetas.h 
	$(CXX) $(CPPFLAGS) $(SRC)/test_receta.cpp -o $(OBJ)/test_receta.o

$(OBJ)/ingredientes.o: $(SRC)/ingredientes.cpp $(INC)/ingredientes.h $(INC)/ingrediente.h
	$(CXX) $(CPPFLAGS) $(SRC)/ingredientes.cpp -o $(OBJ)/ingredientes.o 	

$(OBJ)/ingrediente.o: $(SRC)/ingrediente.cpp $(INC)/ingrediente.h 
	$(CXX) $(CPPFLAGS) $(SRC)/ingrediente.cpp -o $(OBJ)/ingrediente.o 	
	
$(OBJ)/receta.o: $(SRC)/receta.cpp $(INC)/receta.h $(INC)/ingrediente.h $(INC)/ingredientes.h
	$(CXX) $(CPPFLAGS) $(SRC)/receta.cpp -o $(OBJ)/receta.o

$(OBJ)/recetas.o: $(SRC)/recetas.cpp $(INC)/recetas.h $(INC)/receta.h $(INC)/ingrediente.h $(INC)/ingredientes.h
	$(CXX) $(CPPFLAGS) $(SRC)/recetas.cpp -o $(OBJ)/recetas.o

$(OBJ)/nutricion_receta.o: $(SRC)/nutricion_receta.cpp $(INC)/recetas.h $(INC)/receta.h $(INC)/ingrediente.h $(INC)/ingredientes.h
	$(CXX) $(CPPFLAGS) $(SRC)/nutricion_receta.cpp -o $(OBJ)/nutricion_receta.o


# ************ Limpieza ************
clean :
	-rm -f $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm -rf $(BIN)/* doc/html/ doc/latex/

# ************ Entrega *************
entrega: all mrproper
	-rm -f practica3.tgz
	tar -czvf practica3.tgz \
		--exclude-vcs --exclude-vcs-ignores --exclude='datos/*' \
		--exclude='README.md' --exclude='practica3.tgz' \
		../`basename $(PWD)` 
