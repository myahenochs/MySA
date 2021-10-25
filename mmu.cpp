#include "mmu.hpp"

MMU::MMU(Bus *dBus, Bus *aBus, Bus *cBus): dataBus(dBus), addressBus(aBus), cpuBus(cBus){

}

void MMU::SetMAR(uint8_t address){
    mar = address;
}

void MMU::SetMDR(uint8_t data){
    mdr = data;
}