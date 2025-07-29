#include <iostream>

#include "clock.h"
#include  "Decoder.h"
#include "Memory.h"
#include "Rob.h"
std::map<__uint32_t, __uint8_t> Memory::mem;



int main() {

    Memory::store_ins();
    Memory::show_mem();
    while (clock::execute_once()) {std::cerr<<"clk:"<<clock::ticker<<std::endl;}

    return 0;
}

