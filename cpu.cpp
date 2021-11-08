#include "cpu.hpp"

CPU::CPU(Memory *memory, Bus *dataBus, Bus *addressBus): 
    internalBus(new Bus),
    alu{internalBus}, 
    rf{internalBus}, 
    mmu{memory, dataBus, addressBus},
    pc(0)
{}

CPU::~CPU(){
    delete internalBus;
    internalBus = nullptr;
}

void CPU::Fetch(){
    ir = GetNext();
    switch (ir){
        case 0x00: NOP();
            break;
        case 0x01: LDA();
            break;
        case 0x02: LDX();
            break;
        case 0x03: LDY();
            break;
        case 0x04: LDZ();
            break;
        case 0x05: STA();
            break;
        case 0x06: STX();
            break;
        case 0x07: STY();
            break;
        case 0x08: STZ();
            break;
        case 0x09: ADD();
            break;
        case 0x0A: SUB();
            break;
        default: HLT();
    }
}

uint8_t CPU::GetNext(){
    mmu.SetReadWrite(0);
    mmu.SetMAR(pc);
    mmu.Run();
    pc++;
    return mmu.GetMDR();
}

void CPU::NOP(){
    return;
}

void CPU::HLT(){

}

void CPU::LDA(){
    internalBus->data = GetNext();
    rf.StoreRegister(A_REG);
}

void CPU::LDX(){
    internalBus->data = GetNext();
    rf.StoreRegister(X_REG);
}

void CPU::LDY(){
    internalBus->data = GetNext();
    rf.StoreRegister(Y_REG);
}

void CPU::LDZ(){
    internalBus->data = GetNext();
    rf.StoreRegister(Z_REG);
}

void CPU::STA(){
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(A_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::STX(){
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(X_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::STY(){
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(Y_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::STZ(){
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(Z_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::ADD(){

}

void CPU::SUB(){

}

void RST(){
     
}