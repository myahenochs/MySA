#include "mmu.hpp"

MMU::MMU(Memory *memory, Bus *dBus, Bus *aBus, Bus *cBus): ram(memory), dataBus(dBus), addressBus(aBus), cpuBus(cBus){

}

MMU::~MMU(){
    ram = nullptr;
}

void MMU::SetMAR(){
    mar = cpuBus->data;
}

void MMU::SetMDR(){
    mdr = cpuBus->data;
}

void MMU::SetReadWrite(bool flag){
    ram->SetReadWrite(flag);
}

void MMU::Run(){
    dataBus->data = mdr;
    addressBus->data = mar;
    ram->Run();
    mdr = dataBus->data;
}