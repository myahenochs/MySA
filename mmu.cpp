#include "mmu.hpp"

MMU::MMU(Memory *memory, Bus *dBus, Bus *aBus, Bus *cBus): ram(memory), dataBus(dBus), addressBus(aBus), cpuBus(cBus){

}

MMU::~MMU(){
    ram = nullptr;
}

void MMU::SetMAR(uint8_t address){
    mar = address;
    std::cout << "MAR: " << std::hex << std::uppercase << +mar << std::endl;
}

void MMU::SetMDR(uint8_t data){
    mdr = data;
    std::cout << "MDR: " << std::hex << std::uppercase << +mdr << std::endl;
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