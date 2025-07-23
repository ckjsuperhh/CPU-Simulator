//
// Created by ckjsuperhh6602 on 25-7-23.
//

#ifndef CLOCK_H
#define CLOCK_H
#include "Rob.h"

class clock {
public:
    static int ticker;


    static void execute_once() {
        ticker++;
        ROB::execute();
    }




};

#endif //CLOCK_H
