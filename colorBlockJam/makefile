CXX       = g++
CXXFLAGS  = -Wall -Wextra -std=c++17 -g -I include/
BUILD_DIR = build

# =======================================================
# OBJETOS BASE
# =======================================================

OBJS_BASE = \
	$(BUILD_DIR)/Block.o \
	$(BUILD_DIR)/Exit.o \
	$(BUILD_DIR)/Gate.o \
	$(BUILD_DIR)/Cell.o \
	$(BUILD_DIR)/Board.o

# =======================================================
# PARSER
# =======================================================

OBJS_PARSER = \
	$(BUILD_DIR)/BoardParser.o \
	$(BUILD_DIR)/MoveSequence.o

# =======================================================
# MOVIMIENTOS
# =======================================================

OBJS_MOVES = \
	$(BUILD_DIR)/Operation.o \
	$(BUILD_DIR)/MoveUp.o \
	$(BUILD_DIR)/MoveDown.o \
	$(BUILD_DIR)/MoveLeft.o \
	$(BUILD_DIR)/MoveRight.o

# =======================================================
# A*
# =======================================================

OBJS_ASTAR = \
	$(BUILD_DIR)/GameState.o \
	$(BUILD_DIR)/Heap.o \
	$(BUILD_DIR)/ClosedSet.o \
	$(BUILD_DIR)/NeighborGenerator.o \
	$(BUILD_DIR)/Solver.o

# =======================================================
# MAIN
# =======================================================

MAIN_EXEC = $(BUILD_DIR)/main
MAIN_OBJ  = $(BUILD_DIR)/main.o

# =======================================================
# EJECUTABLES TEST
# =======================================================

TEST_BLOCK        = $(BUILD_DIR)/testBlock
TEST_EXIT         = $(BUILD_DIR)/testExit
TEST_GATE         = $(BUILD_DIR)/testGate
TEST_CELL         = $(BUILD_DIR)/testCell
TEST_BOARD        = $(BUILD_DIR)/testBoard
TEST_OPERATION    = $(BUILD_DIR)/testOperation
TEST_GAMESTATE    = $(BUILD_DIR)/testGameState
TEST_SOLVER       = $(BUILD_DIR)/testSolver
TEST_BOARDPARSER  = $(BUILD_DIR)/testBoardParser

# =======================================================
# OBJETOS TEST
# =======================================================

OBJ_TEST_BLOCK        = $(BUILD_DIR)/testBlock.o
OBJ_TEST_EXIT         = $(BUILD_DIR)/testExit.o
OBJ_TEST_GATE         = $(BUILD_DIR)/testGate.o
OBJ_TEST_CELL         = $(BUILD_DIR)/testCell.o
OBJ_TEST_BOARD        = $(BUILD_DIR)/testBoard.o
OBJ_TEST_OP           = $(BUILD_DIR)/testOperation.o
OBJ_TEST_GAMESTATE    = $(BUILD_DIR)/testGameState.o
OBJ_TEST_SOLVER       = $(BUILD_DIR)/testSolver.o
OBJ_TEST_BOARDPARSER  = $(BUILD_DIR)/testBoardParser.o

# =======================================================
# TARGET DEFAULT
# =======================================================

all: \
	$(MAIN_EXEC) \
	$(TEST_BLOCK) \
	$(TEST_EXIT) \
	$(TEST_GATE) \
	$(TEST_CELL) \
	$(TEST_BOARD) \
	$(TEST_OPERATION) \
	$(TEST_GAMESTATE) \
	$(TEST_SOLVER) \
	$(TEST_BOARDPARSER)

# =======================================================
# CREAR BUILD DIR
# =======================================================

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# =======================================================
# BASE
# =======================================================

$(BUILD_DIR)/Block.o: src/Block.cpp include/Block.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Exit.o: src/Exit.cpp include/Exit.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Gate.o: src/Gate.cpp include/Gate.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Cell.o: src/Cell.cpp include/Cell.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Board.o: src/Board.cpp \
	include/Board.h \
	include/Cell.h \
	include/Block.h \
	include/Exit.h \
	include/Gate.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =======================================================
# PARSER + MOVESEQUENCE
# =======================================================

$(BUILD_DIR)/BoardParser.o: src/BoardParser.cpp \
	include/BoardParser.h \
	include/Board.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/MoveSequence.o: src/MoveSequence.cpp \
	include/MoveSequence.h \
	include/Board.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =======================================================
# MOVIMIENTOS
# =======================================================

$(BUILD_DIR)/Operation.o: src/Operation.cpp include/Operation.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/MoveUp.o: src/MoveUp.cpp include/MoveUp.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/MoveDown.o: src/MoveDown.cpp include/MoveDown.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/MoveLeft.o: src/MoveLeft.cpp include/MoveLeft.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/MoveRight.o: src/MoveRight.cpp include/MoveRight.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =======================================================
# A*
# =======================================================

$(BUILD_DIR)/GameState.o: src/GameState.cpp \
	include/GameState.h \
	include/Board.h \
	include/Operation.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Heap.o: src/Heap.cpp \
	include/Heap.h \
	include/GameState.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/ClosedSet.o: src/ClosedSet.cpp \
	include/ClosedSet.h \
	include/GameState.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/NeighborGenerator.o: src/NeighborGenerator.cpp \
	include/NeighborGenerator.h \
	include/GameState.h \
	include/MoveUp.h \
	include/MoveDown.h \
	include/MoveLeft.h \
	include/MoveRight.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Solver.o: src/Solver.cpp \
	include/Solver.h \
	include/Heap.h \
	include/ClosedSet.h \
	include/NeighborGenerator.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =======================================================
# MAIN
# =======================================================

$(BUILD_DIR)/main.o: src/main.cpp \
	include/BoardParser.h \
	include/Solver.h \
	include/MoveSequence.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_EXEC): \
	$(MAIN_OBJ) \
	$(OBJS_PARSER) \
	$(OBJS_ASTAR) \
	$(OBJS_MOVES) \
	$(OBJS_BASE)
	$(CXX) $^ -o $@

# =======================================================
# TESTS OBJETOS
# =======================================================

$(BUILD_DIR)/testBlock.o: test_class/testBlock.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testExit.o: test_class/testExit.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testGate.o: test_class/testGate.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testCell.o: test_class/testCell.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testBoard.o: test_class/testBoard.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testOperation.o: test_class/testOperation.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testGameState.o: test_class/testGameState.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testSolver.o: test_class/testSolver.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/testBoardParser.o: test_class/testBoardParser.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =======================================================
# LINKEO TESTS
# =======================================================

$(TEST_BLOCK): $(OBJ_TEST_BLOCK) $(BUILD_DIR)/Block.o
	$(CXX) $^ -o $@

$(TEST_EXIT): $(OBJ_TEST_EXIT) $(BUILD_DIR)/Exit.o
	$(CXX) $^ -o $@

$(TEST_GATE): $(OBJ_TEST_GATE) $(BUILD_DIR)/Gate.o
	$(CXX) $^ -o $@

$(TEST_CELL): $(OBJ_TEST_CELL) $(BUILD_DIR)/Cell.o
	$(CXX) $^ -o $@

$(TEST_BOARD): $(OBJ_TEST_BOARD) $(OBJS_BASE)
	$(CXX) $^ -o $@

$(TEST_OPERATION): $(OBJ_TEST_OP) $(OBJS_MOVES) $(OBJS_BASE)
	$(CXX) $^ -o $@

$(TEST_GAMESTATE): \
	$(OBJ_TEST_GAMESTATE) \
	$(BUILD_DIR)/GameState.o \
	$(BUILD_DIR)/Heap.o \
	$(OBJS_MOVES) \
	$(OBJS_BASE)
	$(CXX) $^ -o $@

$(TEST_SOLVER): \
	$(OBJ_TEST_SOLVER) \
	$(OBJS_ASTAR) \
	$(OBJS_MOVES) \
	$(OBJS_BASE)
	$(CXX) $^ -o $@

$(TEST_BOARDPARSER): \
	$(OBJ_TEST_BOARDPARSER) \
	$(OBJS_PARSER) \
	$(OBJS_ASTAR) \
	$(OBJS_MOVES) \
	$(OBJS_BASE)
	$(CXX) $^ -o $@

# =======================================================
# RUN INDIVIDUALES
# =======================================================

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

testSolver: $(TEST_SOLVER)
	./$(TEST_SOLVER)

testBoardParser: $(TEST_BOARDPARSER)
	./$(TEST_BOARDPARSER)

# =======================================================
# MAIN
# =======================================================

main: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# =======================================================
# RUN TODOS LOS TESTS
# =======================================================

run: \
	$(TEST_BLOCK) \
	$(TEST_EXIT) \
	$(TEST_GATE) \
	$(TEST_CELL) \
	$(TEST_BOARD) \
	$(TEST_OPERATION) \
	$(TEST_GAMESTATE) \
	$(TEST_SOLVER) \
	$(TEST_BOARDPARSER)
	@echo "\n=== testBlock ===" && ./$(TEST_BLOCK)
	@echo "\n=== testExit ===" && ./$(TEST_EXIT)
	@echo "\n=== testGate ===" && ./$(TEST_GATE)
	@echo "\n=== testCell ===" && ./$(TEST_CELL)
	@echo "\n=== testBoard ===" && ./$(TEST_BOARD)
	@echo "\n=== testOperation ===" && ./$(TEST_OPERATION)
	@echo "\n=== testGameState ===" && ./$(TEST_GAMESTATE)
	@echo "\n=== testSolver ===" && ./$(TEST_SOLVER)
	@echo "\n=== testBoardParser ===" && ./$(TEST_BOARDPARSER)

# =======================================================
# VALGRIND
# =======================================================

valgrind: $(MAIN_EXEC)
	valgrind --leak-check=full ./$(MAIN_EXEC)

# =======================================================
# CLEAN
# =======================================================

clean:
	rm -rf $(BUILD_DIR)