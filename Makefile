# variableS
CXX = g++
CXXFLAGS = -wall -std=c++11
INCLUDES = -Iinclude
SRC = src 
BIN = bin 
OBJ = obj 

# Archivos fuente por modulos
INFRA = $(SRC)src/infraestructura/memoria_compartida.cpp $(SRC)/infraestructura/semaforos.cpp
GENERADOR = $(SRC)src/generador_llamadas/generador.cpp $(SRC)/generador_llamadas/flujo_emergencias.cpp
TEST = $(SRC)src/test/test_integracion.cpp
HEADERS = include/memoria_compartida.h include/semaforos.h

#Archivos objeto
OBJS_INFRA = $(INFRA:%.cpp=$(OBJ)/%.O)

#Compilacion principal
all: $(BIN)/Sistema_Emergencia

#regla para sistema principal (generador + infraestructura)
$(BIN)/Sistema_Emergencia: $(GENERADOR) $(INFRA) $(HEADERS)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(GENERADOR) $(INFRA) $(INCLUDES) -o $@
	@echo "Compilado: Sistema de emergencias"

#compilar test de integracion
test: $(TEST) $(INFRA)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(TEST) $(INFRA) $(INCLUDES) -O $(BIN)/test_integracion
	@echo "Compilado: test_integracion"

# limpiar archivos generados
limpiar: 
	rm -rf $(BIN)/*
	@echo "Proyecto limpio"

#regla por defecto si no se pone ningun objetivo
.PHONY: all test limpiar
