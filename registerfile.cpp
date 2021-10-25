#include "registerfile.hpp"

RegisterFile::RegisterFile(Bus *inputBus): input(inputBus){

}

void RegisterFile::StoreRegister(Register location){
    registerList[location] = input->data;
}

uint8_t RegisterFile::GetRegister(Register location) const{
    return registerList[location];
}