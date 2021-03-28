GCC := gcc

SRC_DIR := ./src
SRC := $(wildcard $(SRC_DIR)/*.c)

INC_DIR := ./inc
INC := $(wildcard $(INC_DIR)/*.h)

UNIT_DIR := ./unit_tests
UNITS := $(wildcard $(UNIT_DIR)/*.c)

OUT_DIR := ./out
OBJECTS := $(SRC:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
OBJ_UNIT := $(UNITS:$(UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
OBJ_UNIT += $(filter-out $(OUT_DIR)/main.o, $(OBJECTS))
FLAGS := -std=c99
U_FLAGS := -lcheck

APPS = app.exe
UNIT_TEST = unit_tests.exe


.PHONY : clean unit


$(APPS): $(OBJECTS)
	$(GCC) $(OBJECTS) -o $@


$(UNIT_TEST): $(OBJ_UNIT)
	$(GCC) $(OBJ_UNIT) -o $@ $(U_FLAGS)


$(OUT_DIR):
	@mkdir -p $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(INC) $(OUT_DIR)
	$(GCC) $(FLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c $(INC) $(OUT_DIR)
	$(GCC) $(FLAGS) -c $< -o $@

unit: $(UNIT_TEST)
	@./$(UNIT_TEST)

clean:
	@rm -rf $(OBJ_DIR) *.exe; \
	echo "Clean OK"
