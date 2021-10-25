#pragma once

#include "system.hpp"
#include <iostream> //temporary

class RegisterFile {

    public:

        enum Register {
            A_REG,
            X_REG,
            Y_REG,
            Z_REG
        };

        RegisterFile(Bus *inputBus);

        void StoreRegister(Register location);
        uint8_t GetRegister(Register location) const;

    private:

        Bus *input;
        uint8_t registerList[4];

};