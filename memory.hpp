#pragma once

#include "system.hpp"

class Memory{

    public:

        const int MAX_SIZE;
        static const int KILOBYTE = 1024;

        Memory(Bus *dataBus, Bus *addressBus, int size=KILOBYTE/8);
        ~Memory();

        void SetReadWrite(bool flag);
        void Run();

    private:

        uint8_t *mem;
        bool rwFlag; //0 read, 1 write
        Bus *dataBus, *addressBus;

};