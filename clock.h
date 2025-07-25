//
// Created by ckjsuperhh6602 on 25-7-23.
//

#ifndef CLOCK_H
#define CLOCK_H
#include "Ins_Cache.h"
#include "Rob.h"

class clock {
public:
    static int ticker;


    static bool execute_once() {
        ticker++;
        Ins_Cache::check();//每一个时钟都要检查一下指令缓存有没有做
        return ROB::execute();
    }




};

#endif //CLOCK_H
