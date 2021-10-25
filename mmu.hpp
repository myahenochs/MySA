#pragma once

#include "system.hpp"
#include "memory.hpp"
#include <iostream> //temporary for testing

class MMU{

    public:

        MMU(Memory *memory, Bus *dataBus, Bus *addressBus, Bus *cpuBus);
        ~MMU();

        void SetMAR();
        void SetMDR();
        void SetReadWrite(bool flag);
        void Run();

        uint8_t GetMDR() const;

    private:

        uint8_t mar, mdr;
        Bus *dataBus, *addressBus, *cpuBus;
        Memory *ram;
        //Address mapping would also be here, 
        //so I'll be adding the pointers for heap, stack, etc.

};