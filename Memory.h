//
// Created by ckjsuperhh6602 on 25-7-22.
//

#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <map>
#include <bits/types.h>
#include "Decoder.h"
inline __uint32_t Binary_Little_Endian(char ins[]){
    unsigned char bytes[4];
    for (int i = 0; i < 4; ++i) {
        const char tmp[3] = { ins[i*2], ins[i*2+1], 0 };
        bytes[i] = static_cast<unsigned char>(strtol(tmp, nullptr, 16));
    }
    return static_cast<__uint32_t>(bytes[3] << 24 | bytes[2] << 16 | bytes[1] << 8 | bytes[0]);
}

class Memory {
public:
    static std::map<__uint32_t,__uint32_t> mem;

    static __uint32_t read(const __uint32_t from) {
       if (!mem.contains(from)) {
           return 0;
       }
        return mem[from];
    }

    static void write(const __uint32_t to,const __uint32_t data) {
        if (!mem.contains(to)) {
            mem.insert({to,data});
        }
        mem[to]=data;
    }

    static void store_ins() {
        char first;
        __uint32_t pc=0;
        while (std::cin>>first) {
            if (first=='@') {
                char addr[9];
                for (int i=0;i<8;i++) {
                    std::cin>>addr[i];
                }
                addr[8]='\0';
                pc=strtol(addr, nullptr, 16);
            }else {
                char ins[9];
                ins[0]=first;
                for (int i=1;i<8;i++) {
                    std::cin>>ins[i];
                    while (ins[i]==' ') {
                        std::cin>>ins[i];
                    }
                }
                ins[8]='\0';
                const __uint32_t instruction=Binary_Little_Endian(ins);
                write(pc,instruction);
                pc+=4;
            }
        }
    }

    static void show_mem() {
        for (const auto &[fst, snd] : mem) {
            std::cout<<std::hex<<fst<<": "<<std::setw(8)<<std::setfill('0')<<snd<<std::endl;
        }
    }
};

class ticker_mem {
public:
    friend class Memory;
    int ticker{};
    __uint32_t pc{},val{};

    ticker_mem()=default;
    explicit ticker_mem(const __uint32_t pc, const __uint32_t val=0):pc(pc){
        this->val=val;
        ticker=0;
    }

    bool read() {
        if (++ticker!=3) {
            return false;
        }
        this->val=Memory::read(pc);
        return true;
    }

    bool write() {
        if (++ticker!=3) {
            return false;
        }
        Memory::write(pc,val);
        return true;
    }
};



#endif //MEMORY_H
