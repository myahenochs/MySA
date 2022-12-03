#include "cpu.hpp"
#include <bitset> //temporary for testing

CPU::CPU(Memory *memory, Bus *dataBus, Bus *addressBus): 
    internalBus(new Bus),
    alu{internalBus}, 
    rf{internalBus}, 
    mmu{memory, dataBus, addressBus},
    pc(0),
    halt(false)
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
        case 0x0B: NOT();
            break;
        case 0x0C: AND();
            break;
        case 0x0D: OR();
            break;
        case 0x0E: XOR();
            break;
        case 0x0F: BSL();
            break;
        case 0x10: BSR();
            break;
        case 0x11: JMP();
            break;
        case 0x12: JMZ();
            break;
        case 0x13: JNZ();
            break;
        case 0x14: HLT();
            break;
        case 0x15: RST();
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

bool CPU::IsHalted() const{
    return halt;
}

void CPU::NOP(){
    return;
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
    alu.SetInstruction(ADD_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::SUB(){
    alu.SetInstruction(SUB_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::NOT(){
    alu.SetInstruction(NOT_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::AND(){
    alu.SetInstruction(AND_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::OR(){
    alu.SetInstruction(OR_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::XOR(){
    alu.SetInstruction(XOR_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::BSL(){
    alu.SetInstruction(BSL_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::BSR(){
    alu.SetInstruction(BSL_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::JMP(){
    pc = GetNext();
}

void CPU::JMZ(){

    if(alu.GetStatus()&ZERO){
        pc = GetNext();
    }
    else{
        GetNext();
    }
}

void CPU::JNZ(){

    if(alu.GetStatus()&ZERO){
        GetNext();
    }
    else{
        pc = GetNext();
    }
}

void CPU::HLT(){
    halt = true;
}

void CPU::RST(){
    pc = 0;
    alu.SetStatus(0x00);
}
