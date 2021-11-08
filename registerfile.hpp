#pragma once

#include "system.hpp"
#include <iostream> //temporary

enum Register {
    A_REG,
    X_REG,
    Y_REG,
    Z_REG
};

class RegisterFile {

    public:

        

        RegisterFile(Bus *inputBus);

        void StoreRegister(Register location);
        uint8_t GetRegister(Register location) const;

    private:

        Bus *input;
        uint8_t registerList[4];

};