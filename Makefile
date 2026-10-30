CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

BIN := bin
EJERCICIOS := ejercicio1 ejercicio2 ejercicio3 ejercicio4

.PHONY: all $(EJERCICIOS) run-ejercicio1 run-ejercicio2 run-ejercicio3 run-ejercicio4 clean

all: $(EJERCICIOS)

ejercicio1: $(BIN)/ejercicio1_par
ejercicio2: $(BIN)/ejercicio2_minimo
ejercicio3: $(BIN)/ejercicio3_potencia
ejercicio4: $(BIN)/ejercicio4_crtp

$(BIN)/ejercicio1_par: ejercicio1-par/main.cpp ejercicio1-par/par.h | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN)/ejercicio2_minimo: ejercicio2-minimo/main.cpp ejercicio2-minimo/minimo.h | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN)/ejercicio3_potencia: ejercicio3-potencia-constexpr/main.cpp ejercicio3-potencia-constexpr/potencia.h | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN)/ejercicio4_crtp: ejercicio4-crtp/main.cpp ejercicio4-crtp/figuras.h | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN):
	mkdir -p $(BIN)

run-ejercicio1: ejercicio1
	./$(BIN)/ejercicio1_par
run-ejercicio2: ejercicio2
	./$(BIN)/ejercicio2_minimo
run-ejercicio3: ejercicio3
	./$(BIN)/ejercicio3_potencia
run-ejercicio4: ejercicio4
	./$(BIN)/ejercicio4_crtp

clean:
	rm -rf $(BIN)
