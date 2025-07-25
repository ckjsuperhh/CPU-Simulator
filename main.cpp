#include <iostream>

#include "clock.h"
#include  "Decoder.h"
#include "Memory.h"
#include "Rob.h"
std::map<__uint32_t, __uint32_t> Memory::mem;



int main() {

    Memory::store_ins();
    while (clock::execute_once()) {}
    std::cout<<clock::ticker<<std::endl;
    return 0;
}

