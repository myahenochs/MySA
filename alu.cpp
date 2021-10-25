#include "alu.hpp"

ALU::ALU(Bus *outputBus): output(outputBus){
    status=0b00000000;
}

void ALU::SetStatus(uint8_t newState){
    status=newState;
}

void ALU::SetInstruction(uint8_t ins){
    instruction=ins;
}

void ALU::SetOp1(uint8_t op){
    op1=op;
}

void ALU::SetOp2(uint8_t op){
    op2=op;
}

void ALU::Run(){
    switch(instruction){
        case ADD_:  buffer = ADD();
                    if(buffer < op1 || buffer < op2){
                        SetStatus(status|OVERFLOW);
                    }
                    break;

        case SUB_:  buffer = SUB();
                    if(buffer > op1){
                        SetStatus(status|NEGATIVE);
                    }
                    break;

        case NOT_:  buffer = NOT();
                    break;

        case AND_:  buffer = AND();
                    break;

        case OR_:   buffer = OR();
                    break;

        case XOR_:  buffer = XOR();
                    break;

        case BSL_:  buffer = BSL();
                    break;
        
        case BSR_:  buffer = BSR();
                    break;

        default:    buffer=0x00;
    }
    
    if(buffer==0){
        SetStatus(status|ZERO);
    }

    output->data = buffer;
}

uint8_t ALU::GetStatus() const{
    return status;
}

uint8_t ALU::ADD(){
    return op1+op2;
}

uint8_t ALU::SUB(){
    return op1-op2;
}

uint8_t ALU::NOT(){
    return ~op1;
}

uint8_t ALU::AND(){
    return op1&op2;
}

uint8_t ALU::OR(){
    return op1|op2;
}

uint8_t ALU::XOR(){
    return op1^op2;
}

uint8_t ALU::BSL(){
    return (op1 << 1);
}

uint8_t ALU::BSR(){
    return (op1 >> 1);
}