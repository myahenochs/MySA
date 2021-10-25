#include "memory.hpp"

Memory::Memory(Bus *dBus, Bus *aBus, int size): MAX_SIZE(size), dataBus(dBus), addressBus(aBus){
    mem = new uint8_t[MAX_SIZE];
}

Memory::~Memory(){
    delete[] mem;
    mem = nullptr;
}

void Memory::SetReadWrite(bool flag){
    rwFlag = flag;
}

void Memory::Run(){
    if(rwFlag){
        mem[addressBus->data] = dataBus->data;
    }
    else{
        dataBus->data = mem[addressBus->data];
    }
}