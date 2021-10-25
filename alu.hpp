#pragma once

#include "system.hpp"

class ALU{
    
    public:

        enum Operation {
            ADD_,
            SUB_,
            NOT_,
            AND_,
            OR_,
            XOR_,
            BSL_,
            BSR_
        };

        ALU(Bus *outputBus);

        void SetStatus(uint8_t status);
        void SetInstruction(uint8_t instruction);
        void SetOp1(uint8_t operation);
        void SetOp2(uint8_t operation);

        void Run();

        uint8_t GetStatus() const;

    private:

        Bus *output;
        uint8_t status, instruction, op1, op2, buffer;

        uint8_t ADD();
        uint8_t SUB();
        uint8_t NOT();
        uint8_t AND();
        uint8_t OR();
        uint8_t XOR();
        uint8_t BSL();
        uint8_t BSR();      
};