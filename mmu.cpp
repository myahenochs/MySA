#include "mmu.hpp"

MMU::MMU(Memory *memory, Bus *dBus, Bus *aBus): ram(memory), dataBus(dBus), addressBus(aBus){

}

MMU::~MMU(){
    ram = nullptr;
}

void MMU::SetMAR(uint8_t address){
    mar = address;
}

void MMU::SetMDR(uint8_t data){
    mdr = data;
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

uint8_t MMU::GetMDR() const{
    return mdr;
}