//
// Created by ckjsuperhh6602 on 25-7-22.
//

#ifndef ALUS_H
#define ALUS_H
#include <iostream>

#include "Decoder.h"
#include "Ins_Cache.h"
#include "RF.h"
#include "Rob.h"

class calculate {
public:
    static void cal(inst & ins) {
        if (ins.op == "add") {
            ins.value=ins.rs1_val+ins.rs2_val;
        }else if (ins.op == "sub") {
            ins.value=ins.rs1_val-ins.rs2_val;
        }else if (ins.op == "and") {
            ins.value=ins.rs1_val&ins.rs2_val;
        }else if (ins.op == "or") {
            ins.value=ins.rs1_val|ins.rs2_val;
        } else if (ins.op == "xor") {
            ins.value=ins.rs1_val^ins.rs2_val;
        } else if (ins.op == "sll") {
            ins.value = ins.rs1_val << ins.rs2_val;
        } else if (ins.op == "srl") {
            ins.value = ins.rs1_val >> ins.rs2_val;
        } else if (ins.op == "sra") {
            ins.value = ins.rs1_val >> ins.rs2_val;//这个有zero和sign,什么意思查一下!
        } else if (ins.op == "slt") {
            ins.value = (ins.rs1_val < ins.rs2_val) ? 1 : 0;
        } else if (ins.op == "sltu") {
            ins.value = (ins.rs1_val < ins.rs2_val) ? 1 : 0; //这边也有unsigned和signed,查一下!
        } else if (ins.op == "addi") {
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "andi") {
            ins.value = ins.rs1_val&ins.imm;
        } else if (ins.op == "ori") {
            ins.value = ins.rs1_val|ins.imm;
        } else if (ins.op == "xori") {
            ins.value = ins.rs1_val^ins.imm;
        } else if (ins.op == "slli") {
            ins.value = ins.rs1_val<<ins.imm;
        } else if (ins.op == "srli") {
            ins.value = ins.rs1_val>>ins.imm;
        } else if (ins.op == "srai") {
            ins.value = ins.rs1_val>>ins.imm;//这俩也要查一下!
        } else if (ins.op == "slti") {
            ins.value = (ins.rs1_val < ins.imm) ? 1 : 0;
        } else if (ins.op == "sltiu") {
            ins.value = (ins.rs1_val < ins.imm) ? 1 : 0; //这俩也要查一下!
        } else if (ins.op == "lb") {//往下许多是用来计算地址
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "lbu") {
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "lh") {
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "lhu") {
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "lw") {
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "sb") {//这三个是计算存储地址
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "sh") {
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "sw") {
            ins.value = ins.rs1_val+ins.imm;
        } else if (ins.op == "beq") {//对于有条件的跳转，我就等到跳转完成之后再清空
            if (ins.rs1_val==ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
                Register::pc=ins.value;
                Ins_Cache::clear(Register::pc);
            }
            Reg_status::Busy_pc=false;
        } else if (ins.op == "bge") {
            if (ins.rs1_val>=ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
                Register::pc=ins.value;
                Ins_Cache::clear(Register::pc);
            }
            Reg_status::Busy_pc=false;
        } else if (ins.op == "bgeu") {
            if (ins.rs1_val>=ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
                Register::pc=ins.value;
                Ins_Cache::clear(Register::pc);
            }
            Reg_status::Busy_pc=false;
        } else if (ins.op == "blt") {
            if (ins.rs1_val<ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
                Register::pc=ins.value;
                Ins_Cache::clear(Register::pc);
            }
            Reg_status::Busy_pc=false;
        } else if (ins.op == "bltu") {
            if (ins.rs1_val<ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
                Register::pc=ins.value;
                Ins_Cache::clear(Register::pc);
            }
            Reg_status::Busy_pc=false;
        } else if (ins.op == "bne") {
            if (ins.rs1_val!=ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
                Register::pc=ins.value;
                Ins_Cache::clear(Register::pc);//clear顺带已经修改过pc的值了(不然内部的值已经维护好了，就是pc读到的位置+4)
            }
            Reg_status::Busy_pc=false;
        } else if (ins.op == "jal") {
            ins.value=ins.pc+4;
            Register::pc=ins.pc+ins.imm;
            Reg_status::Busy_pc=false;
            Ins_Cache::modify(Register::pc);
        } else if (ins.op == "jalr") {
            ins.value=ins.pc+4;
            Register::pc=ins.rs1_val+ins.imm;
            Reg_status::Busy_pc=false;
            Ins_Cache::modify(Register::pc);//把Ins_Cache的指针修改成对应的跳转值
        } else if (ins.op == "auipc") {
            ins.imm<<=12;
            ins.value=ins.imm+ins.pc;
        } else if (ins.op == "lui") {
            ins.imm<<=12;
            ins.value=ins.imm;
        } else if (ins.op == "ebreak") {
            std::cout<<"Asking the debugger to do something"<<std::endl;
        } else if (ins.op == "ecall") {
            std::cout<<"Asking the OS to do something"<<std::endl;
        } else {
            std::cout<<"unknown instruction"<<std::endl;
        }
    }
};


#endif //ALUS_H
