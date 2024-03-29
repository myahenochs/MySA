CC = g++
BIN = mysa
FLAGS = -c -fdiagnostics-color=always -g 
DEPS = cpu.hpp alu.hpp memory.hpp registerfile.hpp system.hpp mmu.hpp
OBJ = main.o cpu.o alu.o memory.o registerfile.o mmu.o

%.o: %.cpp $(DEPS)
	$(CC) $(FLAGS) -o $@ $<

test: $(OBJ)
	$(CC) -o $(BIN) $^