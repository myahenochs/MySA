#include "cpu.hpp"

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
    std::cout << "=== NOP ===" << std::endl;
    return;
}

void CPU::LDA(){
    std::cout << "=== LDA ===" << std::endl;
    internalBus->data = GetNext();
    rf.StoreRegister(A_REG);
}

void CPU::LDX(){
    std::cout << "=== LDX ===" << std::endl;
    internalBus->data = GetNext();
    rf.StoreRegister(X_REG);
}

void CPU::LDY(){
    std::cout << "=== LDY ===" << std::endl;
    internalBus->data = GetNext();
    rf.StoreRegister(Y_REG);
}

void CPU::LDZ(){
    std::cout << "=== LDZ ===" << std::endl;
    internalBus->data = GetNext();
    rf.StoreRegister(Z_REG);
}

void CPU::STA(){
    std::cout << "=== STA ===" << std::endl;
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(A_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::STX(){
    std::cout << "=== STX ===" << std::endl;
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(X_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::STY(){
    std::cout << "=== STY ===" << std::endl;
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(Y_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::STZ(){
    std::cout << "=== STZ ===" << std::endl;
    mmu.SetMAR(GetNext());
    mmu.SetMDR(rf.GetRegister(Z_REG));
    mmu.SetReadWrite(1);
    mmu.Run();
}

void CPU::ADD(){
    std::cout << "=== ADD ===" << std::endl;
    alu.SetInstruction(ADD_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::SUB(){
    std::cout << "=== SUB ===" << std::endl;
    alu.SetInstruction(SUB_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::NOT(){
    std::cout << "=== NOT ===" << std::endl;
    alu.SetInstruction(NOT_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::AND(){
    std::cout << "=== NOT ===" << std::endl;
    alu.SetInstruction(AND_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::OR(){
    std::cout << "=== OR ===" << std::endl;
    alu.SetInstruction(OR_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::XOR(){
    std::cout << "=== XOR ===" << std::endl;
    alu.SetInstruction(XOR_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.SetOp2(GetNext());
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::BSL(){
    std::cout << "=== OR ===" << std::endl;
    alu.SetInstruction(BSL_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::BSR(){
    std::cout << "=== OR ===" << std::endl;
    alu.SetInstruction(BSL_);
    alu.SetOp1(rf.GetRegister(A_REG));
    alu.Run();
    rf.StoreRegister(A_REG);
}

void CPU::JMP(){
    std::cout << "=== JMP ===" << std::endl;
    pc = GetNext();
}

void CPU::JMZ(){
    std::cout << "=== JMZ ===" << std::endl;
    if(alu.GetStatus()&ZERO){
        pc = GetNext();
    }
    else {
        GetNext();
    }
}

void CPU::JNZ(){
    std::cout << "=== JNZ ===" << std::endl;
    if(!alu.GetStatus()&ZERO){
        pc = GetNext();
    }
    else{
        GetNext();
    }
}

void CPU::HLT(){
    std::cout << "=== HLT ===" << std::endl;
    halt = true;
}

void CPU::RST(){
    std::cout << "=== RST ===" << std::endl;
    pc = 0;
    alu.SetStatus(0x00);
}
