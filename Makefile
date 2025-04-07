# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -std=c++11
INCLUDES = -Iinclude
SRC = src
BIN = bin

# Archivos fuente
INFRA = $(SRC)/infraestructura/memoria_compartida.cpp $(SRC)/infraestructura/semaforos.cpp
TEST = $(SRC)/test/test_integracion.cpp

# Regla para compilar el test
test:
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(TEST) $(INFRA) $(INCLUDES) -o $(BIN)/test_integracion
	@echo "Compilado: test_integracion"

# Limpiar binarios
limpiar:
	rm -rf $(BIN)/*
	@echo "Proyecto limpio."

TEST_APRENDIZAJE = src/test/test_aprendizaje.cpp

test_aprendizaje:
	$(CXX) $(CXXFLAGS) $(TEST_APRENDIZAJE) src/infraestructura/memoria_compartida.cpp \
    src/infraestructura/semaforos.cpp src/infraestructura/interfaces.cpp \
    src/aprendizaje/modulo_aprendizaje.cpp -Iinclude -o bin/test_aprendizaje

TEST_INTEGRACION = src/test/test_integracion.cpp

test_integracion:
	$(CXX) $(CXXFLAGS) $(TEST_INTEGRACION) src/infraestructura/memoria_compartida.cpp \
	src/infraestructura/semaforos.cpp src/infraestructura/interfaces.cpp \
	src/aprendizaje/modulo_aprendizaje.cpp -Iinclude -o bin/test_integracion


	
.PHONY: test limpiar
