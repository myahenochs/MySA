#include <iostream> // for demos
#include <fstream>
#include <bitset>
#include "alu.hpp"
#include "registerfile.hpp"
#include "system.hpp"
#include "memory.hpp"
#include "mmu.hpp"
#include "cpu.hpp"

// these functions are used only for debugging and demos
void OutputBus(const Bus *bus);
void OutputStatus(const ALU &alu);
void OutputRegFile(const RegisterFile &rf);
void OutputMemory(Memory &ram, Bus *dBus, Bus *aBus);

int main(int argc, char *argv[]){

    Bus *dBus = new Bus;
    Bus *aBus = new Bus;
    Memory ram(dBus, aBus);
    CPU cpu(&ram, dBus, aBus);
    std::ifstream inFile;
    std::string input, filename;
    int hex = 0x00, inc = 0;

    if (argc != 2) {
        std::cerr << "Error: please provide a single file name as an argument." << std::endl;
        std::exit(1);
    }

    filename = argv[1];
    inFile.open(filename);
    if (!inFile) {
        std::cerr << "Error: unable to open file '" << filename << "'." << std::endl;
        std::exit(1);
    }

    ram.SetReadWrite(1);
    while (inc <= ram.MAX_SIZE && !inFile.eof()){
        inFile >> std::hex >> hex;
        aBus->data = inc;
        dBus->data = hex;
        ram.Run();
        ++inc;
    }
    inFile.close();

    OutputMemory(ram, dBus, aBus);
    std::cout << "Continue? y/n > ";
    input = getchar();
    std::cout << std::endl;

    if(toupper(input.front()) == 'Y' && inc > 0){
        while(cpu.pc <= ram.MAX_SIZE && !cpu.IsHalted()){
            cpu.Fetch();
        }
        std::cout << std::endl;
        OutputRegFile(cpu.rf);
        OutputStatus(cpu.alu);
        OutputMemory(ram, dBus, aBus);
    }

    return 0;
}

void OutputBus(const Bus *bus){
    std::cout << "=========BUS==========" << std::endl << std::endl;
    std::cout << "DEC: " << std::dec << +bus->data << std::endl;
    std::cout << "HEX: " << std::hex << std::uppercase << +bus->data << std::endl;
    std::cout << "BIN: " << std::bitset<8>(bus->data) << std::endl << std::endl;
}

void OutputStatus(const ALU &alu){
    std::cout << "========STATUS========" << std::endl << std::endl;
    uint8_t status = alu.GetStatus();
    std::cout << "STATUS: " << std::bitset<8>(status) << std::endl;
    if(status&NEGATIVE){
        std::cout << "\tNEGATIVE" << std::endl;
    }
    if(status&OVERFLOW){
        std::cout << "\tOVERFLOW" << std::endl;
    }
    if(status&ZERO){
        std::cout << "\tZERO" << std::endl;
    }
    std::cout << std::endl;
}

void OutputRegFile(const RegisterFile &rf){
    std::cout << "======REGISTERS=======" << std::endl << std::endl;
    for(int i = 0; i<4; i++){
        std::cout << "DEC: " << std::dec << +rf.GetRegister((Register)i) << std::endl;
        std::cout << "HEX: " << std::hex << std::uppercase << +rf.GetRegister((Register)i) << std::endl;
        std::cout << "BIN: " << std::bitset<8>(rf.GetRegister((Register)i)) << std::endl << std::endl;
    }
}

void OutputMemory(Memory &ram, Bus *dBus, Bus *aBus){
    std::cout << "======MEMORY=======" << std::endl << std::endl;
    int size = ram.MAX_SIZE;
    ram.SetReadWrite(0);
    for(int i = 1; i < size+1; i++){
        aBus->data=i-1;
        ram.Run();
        if(dBus->data < 0x10){
            std::cout << '0';
        }
        std::cout << std::hex << std::uppercase << +dBus->data;
        if(i%4 == 0){
            std::cout << ' ';
        }
        if(i%16 == 0){
            std::cout << '\n';
        }
    }
    std::cout << std::endl << std::endl;
}