//
// Created by ckjsuperhh6602 on 25-7-23.
//

#ifndef CLOCK_H
#define CLOCK_H
#include "CDB.h"
#include "Ins_Cache.h"
#include "Rob.h"

class clock {
public:
    static int ticker;
    static bool execute_once() {
        if (ticker==228) {
            Memory::show_mem();
        }
        // std::cerr<<"ra="<<std::hex<<Register::regs[1]<<std::endl;
        // std::cerr<<"sp="<<std::hex<<Register::regs[2]<<std::endl;
        // std::cerr<<"s0="<<std::hex<<Register::regs[8]<<std::endl;
        // std::cerr<<"s1="<<std::hex<<Register::regs[9]<<std::endl;
        // std::cerr<<"a0="<<std::hex<<Register::regs[10]<<std::endl;
        // std::cerr<<"a1="<<std::hex<<Register::regs[11]<<std::endl;
        // std::cerr<<"a2="<<std::hex<<Register::regs[12]<<std::endl;
        // std::cerr<<"a3="<<std::hex<<Register::regs[13]<<std::endl;
        // std::cerr<<"a4="<<std::hex<<Register::regs[14]<<std::endl;
        // std::cerr<<"a5="<<std::hex<<Register::regs[15]<<std::endl;
        // std::cerr<<"pc="<<std::hex<<Register::pc<<std::endl;
        // RS::show_everything();
        // Register::show_reg();
        Register::set_zero();
        CDB::execute();
        ticker++;
        Ins_Cache::check();//每一个时钟都要检查一下指令缓存有没有做
        return ROB::execute_1();//很明显，只要有运行，end就会是true，那么就要继续进行下一个回合的运行
    }
};
int clock::ticker=0;
#endif //CLOCK_H
