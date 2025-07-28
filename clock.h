//
// Created by ckjsuperhh6602 on 25-7-23.
//

#ifndef CLOCK_H
#define CLOCK_H
#include "CDB.h"
#include "Ins_Cache.h"
#include "LSB.h"
#include "Rob.h"

class clock {
public:
    static int ticker;
    static bool execute_once() {
        CDB::execute();
        ticker++;
        Ins_Cache::check();//每一个时钟都要检查一下指令缓存有没有做
        return ROB::execute();//很明显，只要有运行，end就会是true，那么就要继续进行下一个回合的运行
    }
};

#endif //CLOCK_H
