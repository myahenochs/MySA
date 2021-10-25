#pragma once

#include "system.hpp"
#include "memory.hpp"
#include <iostream> //temporary for testing

class MMU{

    public:

        MMU(Bus *dataBus, Bus *addressBus, Bus *cpuBus);

        void SetMAR(uint8_t address);
        void SetMDR(uint8_t data);

    private:

        uint8_t mar, mdr;
        Bus *dataBus, *addressBus, *cpuBus;
        //Address mapping would also be here, 
        //so I'll be adding the pointers for heap, stack, etc.
        //This is not a priority at this moment.

};