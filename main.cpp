#include <iostream>
#include <bitset>
#include "alu.hpp"
#include "registerfile.hpp"
#include "system.hpp"
#include "memory.hpp"
#include "mmu.hpp"
#include "cpu.hpp"

void OutputBus(const Bus *bus);
void OutputStatus(const ALU &alu);
void OutputRegFile(const RegisterFile &rf);
void OutputMemory(Memory &ram, Bus *dBus, Bus *aBus);

int main(){

    Bus *dBus = new Bus;
    Bus *aBus = new Bus;
    Memory ram(dBus, aBus);
    CPU cpu(&ram, dBus, aBus);
    MMU mmu(&ram, dBus, aBus);

    ram.SetReadWrite(1);
    dBus->data = 0x22;
    aBus->data = 0x00;
    ram.Run();
    dBus->data = 0x33;
    aBus->data = 0x01;
    ram.Run();
    dBus->data = 0x44;
    aBus->data = 0x02;
    ram.Run();

    OutputMemory(ram, dBus, aBus);
    std::cout << "PC: " << std::hex << std::uppercase << +cpu.pc << std::endl;

    cpu.LDA();
    std::cout << "A: " << std::hex << std::uppercase << +cpu.a << std::endl;
    std::cout << "PC: " << std::hex << std::uppercase << +cpu.pc << std::endl;

    cpu.STA();
    std::cout << "PC: " << std::hex << std::uppercase << +cpu.pc << std::endl;
    std::cout << std::endl;

    OutputMemory(ram, dBus, aBus);

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
        std::cout << "DEC: " << std::dec << +rf.GetRegister((RegisterFile::Register)i) << std::endl;
        std::cout << "HEX: " << std::hex << std::uppercase << +rf.GetRegister((RegisterFile::Register)i) << std::endl;
        std::cout << "BIN: " << std::bitset<8>(rf.GetRegister((RegisterFile::Register)i)) << std::endl << std::endl;
    }
}

void OutputMemory(Memory &ram, Bus *dBus, Bus *aBus){
    int size = ram.MAX_SIZE;
    ram.SetReadWrite(0);
    for(int i = 1; i < size+1; i++){
        aBus->data=i-1;
        ram.Run();
        if(dBus->data<0x10){
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
    std::cout << std::endl;
}