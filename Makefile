# ───── CONFIGURACIÓN GENERAL ─────

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Todos los .cpp en src/
ALL_CPP := $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Todos los .cpp que deben generar binarios (no forman parte del sistema base)
ENTRY_POINTS := $(filter-out $(SRC_DIR)/infraestructura/% $(SRC_DIR)/aprendizaje/%, $(ALL_CPP))
ENTRY_NAMES := $(basename $(notdir $(ENTRY_POINTS)))
ENTRY_OBJS := $(patsubst %,$(BUILD_DIR)/%.o,$(ENTRY_NAMES))
ENTRY_BINS := $(patsubst %,$(BIN_DIR)/%,$(ENTRY_NAMES))

# Archivos fuente del sistema (infraestructura, aprendizaje)
SYSTEM_CPP := $(filter-out $(ENTRY_POINTS),$(ALL_CPP))
SYSTEM_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SYSTEM_CPP))

# ───── COMPILACIÓN ─────

all: $(ENTRY_BINS)

$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(SYSTEM_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Alias: permitir make generador
.PHONY: $(ENTRY_NAMES)
$(ENTRY_NAMES): %: $(BIN_DIR)/%
	@echo "Compilado → bin/$@"

#Ejecutable para generador.cpp
bin/generador: build/generador.o $(SYSTEM_OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^

#objeto de generador.cpp
build/generador.o: src/generador_llamadas/generador.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

#Alias
.PHONY: generador
generador: bin/generador

# ───── LIMPIEZA ─────

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
