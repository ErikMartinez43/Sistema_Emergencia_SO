# ─────────────── CONFIGURACIÓN ───────────────

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Archivos fuente normales y de prueba
SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp" ! -path "$(SRC_DIR)/test/*")
TEST_FILES := $(wildcard $(SRC_DIR)/test/*.cpp)

# Objetos para fuentes normales
SRC_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Nombres de los tests (sin extensión ni ruta)
TEST_NAMES := $(basename $(notdir $(TEST_FILES)))
TEST_OBJS := $(patsubst %,$(BUILD_DIR)/%.o,$(TEST_NAMES))
TEST_BINS := $(patsubst %,$(BIN_DIR)/%,$(TEST_NAMES))

# ─────────────── COMPILACIÓN ───────────────

all: $(TEST_BINS)

# Ejecutables → bin/nombre
$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(SRC_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Objetos de test → build/nombre.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/test/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Objetos de fuentes normales
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Alias para permitir: make test_aprendizaje
.PHONY: $(TEST_NAMES)
$(TEST_NAMES): %: $(BIN_DIR)/%
	@echo "Compilado → bin/$@"

# ─────────────── LIMPIEZA ───────────────

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
