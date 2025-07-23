//
// Created by ckjsuperhh6602 on 25-7-22.
//

#ifndef RF_H
#define RF_H
#include <string>
#include <bits/types.h>

#include "Decoder.h"

class Register {
public:
    static __uint32_t regs[32];
    static __uint32_t Rename_regs[32];
    static std::string reg_num[32];
    Register() {
      initial_set();
    }
    static void initial_set() {
        for (unsigned int & reg : regs) {
            reg=0;
        }
    }
    static std::string get_name(int reg){
        if (reg>=32) {
            return "uk";
        }
        return reg_num[reg];
    }
    static __uint32_t read(const int reg) {
        return regs[reg];
    }

    static void write(const int reg,const __uint32_t num) {
        regs[reg]=num;
    }
};

std::string Register::reg_num[32] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

class Reg_status {
    static bool Busy[32];//yes-1,no-0
    static int Reorder[32];







};

inline int Reorder[32]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
inline bool Busy[32]{};

class Read_regs {
public:
    __uint32_t instruction{};
    std::string op{};
    int pc{},rd{}, rs1_val{}, rs2_val{}, imm{};
    explicit Read_regs(const instructions& ins):instruction(ins.instruction),op(ins.op),pc(-1),rd(ins.rd),rs1_val(ins.rs1),rs2_val(ins.rs2),imm(ins.imm) {}
    bool execute() {
        if (Busy[rs1_val]||Busy[rs2_val]||Busy[1]) {
            return false;
        }
        this->rs1_val=Register::read(rs1_val);
        this->rs2_val=Register::read(rs2_val);
        this->pc=Register::read(1);
        return true;
    }
};


#endif //RF_H
