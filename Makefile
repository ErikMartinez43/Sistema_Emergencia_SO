# Compilador y opciones
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
INCLUDE_DIR = include
BUILD_DIR = build
SRC_DIR = src
INFRA_DIR = $(SRC_DIR)/infraestructura
TEST_DIR = $(SRC_DIR)/test

# Archivos fuente compartidos
SHARED_SRCS = $(INFRA_DIR)/memoria_compartida.cpp $(INFRA_DIR)/semaforos.cpp $(INFRA_DIR)/interfaces.cpp
SHARED_OBJS = $(patsubst $(INFRA_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SHARED_SRCS))

# Detectar automáticamente los archivos de prueba
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SRCS))
TEST_BINS = $(patsubst $(TEST_DIR)/%.cpp,%,$(TEST_SRCS))

# Regla por defecto: compilar todos los binarios de prueba
all: $(TEST_BINS)

# Regla general para compilar ejecutables de prueba
%: $(BUILD_DIR)/%.o $(SHARED_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar objetos de pruebas
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilar objetos compartidos
$(BUILD_DIR)/%.o: $(INFRA_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Crear la carpeta build si no existe
$(shell mkdir -p $(BUILD_DIR))

# Limpiar binarios y objetos
clean:
	rm -f $(BUILD_DIR)/*.o $(TEST_BINS)
