//
// Created by ckjsuperhh6602 on 25-7-22.
//

#ifndef ALUS_H
#define ALUS_H
#include <iostream>

#include "Decoder.h"
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
        } else if (ins.op == "beq") {
            if (ins.rs1_val==ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
            }
        } else if (ins.op == "bge") {
            if (ins.rs1_val>=ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
            }
        } else if (ins.op == "bgeu") {
            if (ins.rs1_val<ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
            }
        } else if (ins.op == "blt") {
            if (ins.rs1_val!=ins.rs2_val) {
                ins.value=ins.pc+ins.imm;
            }
        } else if (ins.op == "bltu") {

        } else if (ins.op == "bne") {

        } else if (ins.op == "jal") {

        } else if (ins.op == "jalr") {

        } else if (ins.op == "auipc") {

        } else if (ins.op == "lui") {

        } else if (ins.op == "ebreak") {

        } else if (ins.op == "ecall") {

        } else if (ins.op == "mul") {

        } else {
            std::cout<<"unknown instruction"<<std::endl;
        }
    }
};


#endif //ALUS_H
