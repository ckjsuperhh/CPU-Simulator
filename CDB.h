//
// Created by ckjsuperhh6602 on 25-7-24.
//

#ifndef CDB_H
#define CDB_H
#include <bits/types.h>

enum Pos {
    RS,RF,Mem,Rob
};
class CDB {//广播之后需要把RS和ROB中的相关值进行修改，保证RS我可以判断值是否准备好了，而ROB_Table中的inst的reg_val修改掉
public:
    struct update_info {
        Pos p;
        __uint32_t previous_data,new_data;
    };





};
#endif //CDB_H
