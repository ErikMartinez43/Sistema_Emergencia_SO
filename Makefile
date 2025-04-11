# ─── CONFIGURACIÓN GENERAL ───
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE_DIR := include

# Crear directorios automáticamente
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# ─── ARCHIVOS FUENTE BASE (compartidos) ───
BASE_SRCS := \
    $(SRC_DIR)/infraestructura/memoria_compartida.cpp \
    $(SRC_DIR)/infraestructura/semaforos.cpp \
    $(SRC_DIR)/infraestructura/interfaces.cpp \
    $(SRC_DIR)/infraestructura/gestor_jornadas.cpp \
    $(SRC_DIR)/aprendizaje/modulo_aprendizaje.cpp

BASE_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(BASE_SRCS))

# ─── BINARIOS A COMPILAR ───
BINARIOS := generador comisaria subestacion patrulla hospital ambulancia bomberos vehiculos_bomberos main

# Reglas de compilación de binarios
all: $(BINARIOS)

# Compilar ejecutables finales
$(BINARIOS): %: $(BIN_DIR)/%
	@echo "✅ Compilado: $(BIN_DIR)/$@"

$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(BASE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ─── OBJETOS PARA BINARIOS ───

# main.cpp
$(BUILD_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# generador (caso especial, ubicación diferente)
$(BUILD_DIR)/generador.o: $(SRC_DIR)/generador_llamadas/generador.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# objetos para unidades
$(BUILD_DIR)/%.o: $(SRC_DIR)/unidades/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# objetos para infraestructura y aprendizaje
$(BUILD_DIR)/infraestructura/%.o: $(SRC_DIR)/infraestructura/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/aprendizaje/%.o: $(SRC_DIR)/aprendizaje/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# ─── LIMPIEZA ───
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean $(BINARIOS)