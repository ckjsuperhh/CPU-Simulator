#include <iostream>

#include  "Decoder.h"

int mem[1000000];
int reg[32];


__uint32_t Binary_Little_Endian(char ins[]){
unsigned char bytes[4];
for (int i = 0; i < 4; ++i) {
    const char tmp[3] = { ins[i*2], ins[i*2+1], 0 };
    bytes[i] = static_cast<unsigned char>(strtol(tmp, nullptr, 16));
}
return static_cast<__uint32_t>(bytes[3] << 24 | bytes[2] << 16 | bytes[1] << 8 | bytes[0]);
}

int main() {
    char first;
    while (std::cin>>first) {
        if (first=='@') {
            char addr[8];
            for (char & i : addr) {
                std::cin>>i;
            }
            std::cout<<"@"<<addr<<":"<<std::endl;
        }else {
            char ins[8];
            ins[0]=first;
            for (int i=1;i<8;i++) {
                std::cin>>ins[i];
                while (ins[i]==' ') {
                    std::cin>>ins[i];
                }
            }
            const __uint32_t instruction=Binary_Little_Endian(ins);
            instructions(instruction).show();
        }
    }
}

