//
// Created by ckjsuperhh6602 on 25-7-22.
//

#ifndef ROB_H
#define ROB_H
#include <string>

#include "Decoder.h"

enum State {
    Waiting,Decoded,Issue,Exec,Write,Commit
};
struct inst{
        std::string op;
        int rd{},rs1{},rs2{},imm{};
        State st;
        int value{};
    explicit inst(const instructions& a):
    op(a.op),rd(a.rd),rs1(a.rs1),rs2(a.rs2),imm(a.imm),st(Waiting) {}
};
class ROB {
    static int head;
    static int tail;
    static inst ROB_Table[10000];
    static void execute() {



    };
};

inline int head=0;
inline int tail=0;

#endif //ROB_H
