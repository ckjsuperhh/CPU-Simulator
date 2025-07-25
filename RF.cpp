//
// Created by ckjsuperhh6602 on 25-7-24.
//
#include "RF.h"
#include "Rob.h"

// ==== Register 静态成员初始化 ====
uint32_t Register::regs[32] = {0};
uint32_t Register::Rename_regs[32] = {0};
std::string Register::reg_num[32] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

// Register成员函数实现
Register::Register() { initial_set(); }

void Register::initial_set() {
    for (auto &reg : regs) reg = 0;
}
std::string Register::get_name(int reg) {
    if (reg >= 32) return "uk";
    return reg_num[reg];
}
uint32_t Register::read(const int reg) {
    return regs[reg];
}
void Register::write(const int reg, const uint32_t num) {
    regs[reg] = num;
}
bool Busy_pc=false;
bool Reg_status::Busy[32] = {false};
int Reg_status::Reorder[32] = {
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1
};
bool Reg_status::get_busy(const int idx) {
    if (idx < 0 || idx >= 32) return false;
    return Busy[idx];
}

Read_regs::Read_regs(const instructions& ins)
    : instruction(ins.instruction), op(ins.op), pc(-1), rd(ins.rd),
      rs1_val(ins.rs1), rs2_val(ins.rs2), imm(ins.imm) {}

Read_regs::Read_regs(const inst& ins)
    : op(ins.op), pc(-1), rd(ins.rd),
      rs1_val(ins.rs1), rs2_val(ins.rs2), imm(ins.imm) {}

void Read_regs::execute(inst& ins,int & Vj,int&Vk,int & Qj,int & Qk,int &Dest,int & A) {//不需要顺带读pc了,只需要读需要的部分
    if (double_reg.contains(op)) {
        if (Reg_status::Busy[ins.rs1]) {
            Qj=Reg_status::Reorder[ins.rs1];
            Vj=-1;
        }else {//Vj
            Vj = Register::read(ins.rs1);
            Qj=-1;
        }
        if (Reg_status::Busy[ins.rs2]) {
            Qk=Reg_status::Reorder[ins.rs2];
            Vk=-1;
        }else {//Vk
            Vk = Register::read(ins.rs2);
            Qk=-1;
        }
        return;
    }
    if (first_reg.contains(op)) {
        if (Reg_status::Busy[rs1_val]) {
            Qj=Reg_status::Reorder[ins.rs1];
            Vj=-1;
        }else {//Vj
            Vj = Register::read(ins.rs1);
            Qj=-1;
        }
        Vk=imm;
        Qk=-1;
        return;
    }
    if (only_pc.contains(op)) {
        Qk=Qj=-1;
        Vk=imm;
    }
    //"embreak" and "ecall"
}
int Register::read_pc() {//如果失败就返回-1,不然就是正常值
        if (Busy_pc) {
            return -1;
        }
        return pc;
    }

