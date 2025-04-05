# Compilador y banderas
CXX = g++                         # Compilador a usar
CXXFLAGS = -Wall -std=c++11       # Activar advertencias y usar C++11
INCLUDES = -Iinclude              # Incluir archivos de cabecera personalizados
SRC = src                         # Carpeta de código fuente
BIN = bin                         # Carpeta donde guardaremos binarios

# Archivos fuente usados para el test
INFRA = $(SRC)/infraestructura/memoria_compartida.cpp $(SRC)/infraestructura/semaforos.cpp
TEST = $(SRC)/test/test_integracion.cpp

# Regla para compilar el ejecutable de prueba
test:
	@mkdir -p $(BIN)                                  # Crea carpeta bin si no existe
	$(CXX) $(CXXFLAGS) $(TEST) $(INFRA) $(INCLUDES) -o $(BIN)/test_integracion
	@echo "✅ Compilado: test_integracion"

# Regla para limpiar binarios
limpiar:
	rm -rf $(BIN)/*
	@echo "🧹 Proyecto limpio."

# Declarar las reglas como "phony" para que Make no busque archivos con ese nombre
.PHONY: test limpiar
