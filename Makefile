CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic
BIN := bin

BVA := $(BIN)/bva
DTT := $(BIN)/dtt

.PHONY: all clean bva dtt run

all: $(BVA) $(DTT)

clean:
	@echo "Cleaning $(BIN)/ ..."
	@rm -rf "$(BIN)"

bva: $(BVA)
dtt: $(DTT)

ifeq ($(filter bva,$(MAKECMDGOALS)),bva)
  RUN_TARGET := bva
endif
ifeq ($(filter dtt,$(MAKECMDGOALS)),dtt)
  RUN_TARGET := dtt
endif

run:
	@if [ -z "$(RUN_TARGET)" ]; then \
	  echo "Usage: make run bva|dtt"; exit 1; \
	fi
	@$(MAKE) $(RUN_TARGET)
	@echo "Running $(BIN)/$(RUN_TARGET)..."
	@$(BIN)/$(RUN_TARGET)

$(BIN):
	@mkdir -p "$(BIN)"

$(BVA): boundary_values_analysis.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(DTT): decision_table_testing.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@
