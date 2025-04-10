# ───── CONFIGURACIÓN GENERAL ─────

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Archivos fuente base (infraestructura y aprendizaje)
BASE_CPP := $(shell find $(SRC_DIR)/infraestructura $(SRC_DIR)/aprendizaje -name "*.cpp")
BASE_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(BASE_CPP))

# Ejecutables (todo lo demás)
EXEC_CPP := $(shell find $(SRC_DIR) -type f -name "*.cpp" ! -path "$(SRC_DIR)/infraestructura/*" ! -path "$(SRC_DIR)/aprendizaje/*")
EXEC_NAMES := $(basename $(notdir $(EXEC_CPP)))
EXEC_BINS := $(patsubst %, $(BIN_DIR)/%, $(EXEC_NAMES))
EXEC_OBJS := $(patsubst %, $(BUILD_DIR)/%.o, $(EXEC_NAMES))

# ───── REGLAS PRINCIPALES ─────

all: $(EXEC_BINS)

# Ejecutables
$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(BASE_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Objetos individuales
$(BUILD_DIR)/%.o: 
	@mkdir -p $(dir $@)
	@src_file=$(shell find $(SRC_DIR) -type f -name $*.cpp); \
	if [ -z "$$src_file" ]; then \
		echo "❌ Archivo fuente '$*.cpp' no encontrado en $(SRC_DIR)"; \
		exit 1; \
	fi; \
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $$src_file -o $@

# Alias: make test_funcionamiento, generador, etc.
.PHONY: $(EXEC_NAMES)
$(EXEC_NAMES): %: $(BIN_DIR)/%
	@echo "✅ Compilado: bin/$@"

# Limpieza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

