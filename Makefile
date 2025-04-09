# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Directorios
SRC_DIR = src
TEST_DIR = src/test
INFRA_DIR = src/infraestructura
BUILD_DIR = build
INCLUDE_DIR = include

# Archivos fuente y objetos
OBJS = \
	$(BUILD_DIR)/memoria_compartida.o \
	$(BUILD_DIR)/semaforos.o \
	$(BUILD_DIR)/test_integracion.o

# Ejecutable
TARGET = test_integracion

# Regla por defecto
all: $(TARGET)

# Vinculación final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilación de objetos
$(BUILD_DIR)/memoria_compartida.o: $(INFRA_DIR)/memoria_compartida.cpp $(INCLUDE_DIR)/memoria_compartida.h $(INCLUDE_DIR)/tipos.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/semaforos.o: $(INFRA_DIR)/semaforos.cpp $(INCLUDE_DIR)/semaforos.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/test_integracion.o: $(TEST_DIR)/test_integracion.cpp $(INCLUDE_DIR)/memoria_compartida.h $(INCLUDE_DIR)/semaforos.h
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpieza
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

# Carpeta build si no existe
$(shell mkdir -p $(BUILD_DIR))
