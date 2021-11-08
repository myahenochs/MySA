#pragma once

#include "system.hpp"
#include "memory.hpp"

class MMU{

    public:

        MMU(Memory *memory, Bus *dataBus, Bus *addressBus);
        ~MMU();

        void SetMAR(uint8_t address);
        void SetMDR(uint8_t data);
        void SetReadWrite(bool flag);
        void Run();

        uint8_t GetMDR() const;

    private:

        uint8_t mar, mdr;
        Bus *dataBus, *addressBus, *cpuBus;
        Memory *ram;
};