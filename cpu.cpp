#include "cpu.hpp"

CPU::CPU(Memory *memory, Bus *dataBus, Bus *addressBus): 
    internalBus(new Bus),
    alu{internalBus}, 
    rf{internalBus}, 
    mmu{memory, dataBus, addressBus, internalBus},
    pc(0)
{}

CPU::~CPU(){
    delete internalBus;
    internalBus = nullptr;
}

void CPU::Fetch(){
    ir = GetNext();
}

uint8_t CPU::GetNext(){
    mmu.SetReadWrite(0);
    mmu.SetMAR(pc);
    mmu.Run();
    pc++;
    return mmu.GetMDR();
}

void HLT(){

}

void CPU::LDA(){
    a = GetNext();
}

void CPU::LDX(){
    x = GetNext();
}

void CPU::LDY(){
    y = GetNext();
}

void CPU::LDZ(){
    z = GetNext();
}

void CPU::STA(){
    mmu.SetReadWrite(1);
    mmu.SetMAR(GetNext());
    mmu.SetMDR(a);
    mmu.Run();
}

void RST(){
    
}