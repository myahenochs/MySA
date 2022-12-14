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
        //Fetches next instruction and stores it in the IR.
            //mar <- pc
            //mdr <- M[mar]
            //ir <- mdr
        uint8_t GetNext();
        //Fetches the next byte at the location of the PC, then increments the PC. Returns the contents of the MDR.
            //mar <- pc
            //mdr <- M[mar]
            //
        bool IsHalted() const;

    public: //temporary for testing

        Bus *internalBus;
        ALU alu;
        RegisterFile rf;
        MMU mmu;

        uint8_t ir, pc;
        bool halt;

        void NOP();
            //Returns without any operations being done.

        void LDA();
            //mar <- pc
            //mdr <- M[mar]
            //a <- mdr

        void LDX();
            //mar <- pc
            //mdr <- M[mar]
            //x <- mdr

        void LDY();
            //mar <- pc
            //mdr <- M[mar]
            //y <- mdr

        void LDZ();
            //mar <- pc
            //mdr <- M[mar]
            //z <- mdr

        void STA();
            //mar <- pc
            //mar <- M[mar]
            //mdr <- a
            //M[mar] <- mdr

        void STX();
            //mar <- pc
            //mar <- M[mar]
            //mdr <- x
            //M[mar] <- mdr

        void STY();
            //mar <- pc
            //mar <- M[mar]
            //mdr <- y
            //M[mar] <- mdr

        void STZ();
            //mar <- pc
            //mar <- M[mar]
            //mdr <- z
            //M[mar] <- mdr

        void ADD();
            //ALUA <- a
            //mar <- pc
            //mdr <- M[mar]
            //ALUB <- mdr
            //a <- ALUA + ALUB

        void SUB();
            //ALUA <- a
            //mar <- pc
            //mdr <- M[mar]
            //ALUB <- mdr
            //a <- ALUA - ALUB

        void NOT();
            //ALUA <- a
            //a <- ~ALUA

        void AND();
            //ALUA <- a
            //mar <- pc
            //mdr <- M[mar]
            //ALUB <- mdr
            //a <- ALUA & ALUB

        void OR();
            //ALUA <- a
            //mar <- pc
            //mdr <- M[mar]
            //ALUB <- mdr
            //a <- ALUA | ALUB

        void XOR();
            //ALUA <- a
            //mar <- pc
            //mdr <- M[mar]
            //ALUB <- mdr
            //a <- ALUA (+) ALUB

        void BSL();
            //ALUA <- a
            //a <- <<ALUA

        void BSR();
            //ALUA <- a
            //a <- >>ALUA

        void JMP();

        void JMZ();

        void JNZ();

        void HLT();
            //Stops the CPU

        void RST();
            //pc <- 0
            //status <- 0

};
