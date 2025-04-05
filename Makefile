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
	
.PHONY: test limpiar
