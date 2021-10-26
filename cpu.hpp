#pragma once

#include <iostream> //temporary for testing
#include "system.hpp"
#include "alu.hpp"
#include "registerfile.hpp"
#include "mmu.hpp"

class CPU{

    public:

        CPU(Memory *memory, Bus *dataBus, Bus *addressBus); //Pointer to memory is only needed here because we are not doing parallel programming.
        ~CPU();

        void Fetch();
        uint8_t GetNext();

    public:

        Bus *internalBus;
        ALU alu;
        RegisterFile rf;
        MMU mmu;

        uint8_t ir, pc, a, x, y, z;

        void HLT();
        void LDA();
            //mar <- pc
            //address bus <- mar
            //memory returns data
            //mdr <- data bus
            //a <- mdr
        void LDX();
            //mar <- pc
            //address bus <- mar
            //memory returns data
            //mdr <- data bus
            //x <- mdr
        void LDY();
            //mar <- pc
            //address bus <- mar
            //memory returns data
            //mdr <- data bus
            //y <- mdr
        void LDZ();
            //mar <- pc
            //address bus <- mar
            //memory returns data
            //mdr <- data bus
            //z <- mdr
        void STA();
            //mdr <- a
            //mar <
        void STX();
        void STY();
        void STZ();
        void ADD();
        void SUB();
        void MLT();

};