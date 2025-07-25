//
// Created by ckjsuperhh6602 on 25-7-24.
//

#ifndef CDB_H
#define CDB_H
#include <bits/types.h>

enum Pos {
    RS,RF,Mem,Rob
};
class CDB {
public:
    struct update_info {
        Pos p;
        __uint32_t previous_data,new_data;
    };





};
#endif //CDB_H
