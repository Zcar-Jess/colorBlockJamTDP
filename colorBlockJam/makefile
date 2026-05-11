CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -I include/
BUILD_DIR = build

# -------------------------------------------------------
# Grupos de objetos base (compartidos entre tests)
# -------------------------------------------------------
OBJS_BASE  = $(BUILD_DIR)/Block.o $(BUILD_DIR)/Exit.o $(BUILD_DIR)/Gate.o \
             $(BUILD_DIR)/Cell.o  $(BUILD_DIR)/Board.o
OBJS_MOVES = $(BUILD_DIR)/Operation.o $(BUILD_DIR)/MoveUp.o \
             $(BUILD_DIR)/MoveDown.o  $(BUILD_DIR)/MoveLeft.o \
             $(BUILD_DIR)/MoveRight.o

# -------------------------------------------------------
# Targets de test
# -------------------------------------------------------
TEST_BLOCK     = $(BUILD_DIR)/testBlock
TEST_EXIT      = $(BUILD_DIR)/testExit
TEST_GATE      = $(BUILD_DIR)/testGate
TEST_CELL      = $(BUILD_DIR)/testCell
TEST_BOARD     = $(BUILD_DIR)/testBoard
TEST_OPERATION = $(BUILD_DIR)/testOperation
TEST_GAMESTATE     = $(BUILD_DIR)/testGameState

# -------------------------------------------------------
# Objetos fuente
# -------------------------------------------------------
OBJ_BLOCK     = $(BUILD_DIR)/Block.o
OBJ_EXIT      = $(BUILD_DIR)/Exit.o
OBJ_GATE      = $(BUILD_DIR)/Gate.o
OBJ_CELL      = $(BUILD_DIR)/Cell.o
OBJ_BOARD     = $(BUILD_DIR)/Board.o
OBJ_OPERATION = $(BUILD_DIR)/Operation.o
OBJ_MOVEUP    = $(BUILD_DIR)/MoveUp.o
OBJ_MOVEDOWN  = $(BUILD_DIR)/MoveDown.o
OBJ_MOVELEFT  = $(BUILD_DIR)/MoveLeft.o
OBJ_MOVERIGHT = $(BUILD_DIR)/MoveRight.o
OBJ_GAMESTATE      = $(BUILD_DIR)/GameState.o
OBJ_HEAP           = $(BUILD_DIR)/Heap.o

# -------------------------------------------------------
# Objetos de test
# -------------------------------------------------------
OBJ_TEST_BLOCK = $(BUILD_DIR)/testBlock.o
OBJ_TEST_EXIT  = $(BUILD_DIR)/testExit.o
OBJ_TEST_GATE  = $(BUILD_DIR)/testGate.o
OBJ_TEST_CELL  = $(BUILD_DIR)/testCell.o
OBJ_TEST_BOARD = $(BUILD_DIR)/testBoard.o
OBJ_TEST_OP    = $(BUILD_DIR)/testOperation.o
OBJ_TEST_GAMESTATE = $(BUILD_DIR)/testGameState.o

# -------------------------------------------------------
# Default: compila todos los tests
# -------------------------------------------------------
all: $(TEST_BLOCK) $(TEST_EXIT) $(TEST_GATE) $(TEST_CELL) \
     $(TEST_BOARD) $(TEST_OPERATION) $(TEST_GAMESTATE)

# -------------------------------------------------------
# Crear carpeta build si no existe
# -------------------------------------------------------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# -------------------------------------------------------
# Compilacion de objetos fuente
# -------------------------------------------------------
$(OBJ_BLOCK): src/Block.cpp include/Block.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_EXIT): src/Exit.cpp include/Exit.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_GATE): src/Gate.cpp include/Gate.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_CELL): src/Cell.cpp include/Cell.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_BOARD): src/Board.cpp include/Board.h include/Cell.h \
              include/Block.h include/Exit.h include/Gate.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_OPERATION): src/Operation.cpp include/Operation.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_MOVEUP): src/MoveUp.cpp include/MoveUp.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_MOVEDOWN): src/MoveDown.cpp include/MoveDown.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_MOVELEFT): src/MoveLeft.cpp include/MoveLeft.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_MOVERIGHT): src/MoveRight.cpp include/MoveRight.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_GAMESTATE): src/GameState.cpp include/GameState.h include/Board.h include/Operation.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_HEAP): src/Heap.cpp include/Heap.h include/GameState.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------------------------------------------------------
# Compilacion de objetos de test
# -------------------------------------------------------
$(OBJ_TEST_BLOCK): test_class/testBlock.cpp include/Block.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_TEST_EXIT): test_class/testExit.cpp include/Exit.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_TEST_GATE): test_class/testGate.cpp include/Gate.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_TEST_CELL): test_class/testCell.cpp include/Cell.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_TEST_BOARD): test_class/testBoard.cpp include/Board.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_TEST_OP): test_class/testOperation.cpp include/Board.h \
                include/MoveUp.h include/MoveDown.h \
                include/MoveLeft.h include/MoveRight.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_TEST_GAMESTATE): test_class/testGameState.cpp include/GameState.h include/Heap.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------------------------------------------------------
# Linkeo de ejecutables de test
# -------------------------------------------------------
$(TEST_BLOCK): $(OBJ_TEST_BLOCK) $(OBJ_BLOCK)
	$(CXX) $^ -o $@

$(TEST_EXIT): $(OBJ_TEST_EXIT) $(OBJ_EXIT)
	$(CXX) $^ -o $@

$(TEST_GATE): $(OBJ_TEST_GATE) $(OBJ_GATE)
	$(CXX) $^ -o $@

$(TEST_CELL): $(OBJ_TEST_CELL) $(OBJ_CELL)
	$(CXX) $^ -o $@

$(TEST_BOARD): $(OBJ_TEST_BOARD) $(OBJS_BASE)
	$(CXX) $^ -o $@

$(TEST_OPERATION): $(OBJ_TEST_OP) $(OBJS_MOVES) $(OBJS_BASE)
	$(CXX) $^ -o $@

$(TEST_GAMESTATE): $(OBJ_TEST_GAMESTATE) $(OBJ_GAMESTATE) $(OBJ_HEAP) \
                   $(OBJS_MOVES) $(OBJS_BASE)
	$(CXX) $^ -o $@

# -------------------------------------------------------
# Correr tests individuales
# -------------------------------------------------------
testBlock: $(TEST_BLOCK)
	./$(TEST_BLOCK)

testExit: $(TEST_EXIT)
	./$(TEST_EXIT)

testGate: $(TEST_GATE)
	./$(TEST_GATE)

testCell: $(TEST_CELL)
	./$(TEST_CELL)

testBoard: $(TEST_BOARD)
	./$(TEST_BOARD)

testOperation: $(TEST_OPERATION)
	./$(TEST_OPERATION)

testGameState: $(TEST_GAMESTATE)
	./$(TEST_GAMESTATE)

# -------------------------------------------------------
# Correr todos los tests
# -------------------------------------------------------
run: all
	@echo "\n=== Corriendo testBlock ==="
	./$(TEST_BLOCK)
	@echo "\n=== Corriendo testExit ==="
	./$(TEST_EXIT)
	@echo "\n=== Corriendo testGate ==="
	./$(TEST_GATE)
	@echo "\n=== Corriendo testCell ==="
	./$(TEST_CELL)
	@echo "\n=== Corriendo testBoard ==="
	./$(TEST_BOARD)
	@echo "\n=== Corriendo testOperation ==="
	./$(TEST_OPERATION)
	@echo "\n=== Corriendo testGameState ==="
	./$(TEST_GAMESTATE)

# -------------------------------------------------------
# Valgrind (detectar memory leaks)
# -------------------------------------------------------
valgrind: all
	valgrind --leak-check=full ./$(TEST_BLOCK)
	valgrind --leak-check=full ./$(TEST_EXIT)
	valgrind --leak-check=full ./$(TEST_GATE)
	valgrind --leak-check=full ./$(TEST_CELL)
	valgrind --leak-check=full ./$(TEST_BOARD)
	valgrind --leak-check=full ./$(TEST_OPERATION)

# -------------------------------------------------------
# Limpiar build
# -------------------------------------------------------
clean:
	rm -rf $(BUILD_DIR)