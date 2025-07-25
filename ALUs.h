//
// Created by ckjsuperhh6602 on 25-7-22.
//

#ifndef ALUS_H
#define ALUS_H
#include <iostream>

#include "Decoder.h"
#include "RF.h"

class calculate {
public:
    __uint32_t instruction{};
    std::string op{};
    int rd{}, rs1_val{}, rs2_val{}, imm{},value{},value_{};
    std::string type{};
    explicit calculate(const Read_regs& ins):instruction(ins.instruction),op(ins.op),pc(ins.pc),rd(ins.rd),rs1_val(ins.rs1_val),rs2_val(ins.rs2_val),imm(ins.imm) {}
    calculate();
    calculate cal() {
        if (op == "add") {
            value=rs1_val+rs2_val;
        }else if (op == "sub") {
            value=rs1_val-rs2_val;
        }else if (op == "and") {
            value=rs1_val&rs2_val;
        }else if (op == "or") {
            value=rs1_val|rs2_val;
        } else if (op == "xor") {
            value=rs1_val^rs2_val;
        } else if (op == "sll") {
            value = rs1_val << rs2_val;
        } else if (op == "srl") {
            value = rs1_val >> rs2_val;
        } else if (op == "sra") {
            value = rs1_val >> rs2_val;//这个有zero和sign,什么意思查一下!
        } else if (op == "slt") {
            value = (rs1_val < rs2_val) ? 1 : 0;
        } else if (op == "sltu") {
            value = (rs1_val < rs2_val) ? 1 : 0; //这边也有unsigned和signed,查一下!
        } else if (op == "addi") {
            value = rs1_val+imm;
        } else if (op == "andi") {
            value = rs1_val&imm;
        } else if (op == "ori") {
            value = rs1_val|imm;
        } else if (op == "xori") {
            value = rs1_val^imm;
        } else if (op == "slli") {
            value = rs1_val<<imm;
        } else if (op == "srli") {
            value = rs1_val>>imm;
        } else if (op == "srai") {
            value = rs1_val>>imm;//这俩也要查一下!
        } else if (op == "slti") {
            value = (rs1_val < imm) ? 1 : 0;
        } else if (op == "sltiu") {
            value = (rs1_val < imm) ? 1 : 0; //这俩也要查一下!
        } else if (op == "lb") {//往下许多是用来计算地址
            value = rs1_val+imm;
        } else if (op == "lbu") {
            value = rs1_val+imm;
        } else if (op == "lh") {
            value = rs1_val+imm;
        } else if (op == "lhu") {
            value = rs1_val+imm;
        } else if (op == "lw") {
            value = rs1_val+imm;
        } else if (op == "sb") {//这三个是计算存储地址
            value = rs1_val+imm;
        } else if (op == "sh") {
            value = rs1_val+imm;
        } else if (op == "sw") {
            value = rs1_val+imm;
        } else if (op == "beq") {
            if (rs1_val==rs2_val) {
                value=pc+imm;
            }
        } else if (op == "bge") {
            if (rs1_val>=rs2_val) {
                value=pc+imm;
            }
        } else if (op == "bgeu") {
            if (rs1_val<rs2_val) {
                value=pc+imm;
            }
        } else if (op == "blt") {
            if (rs1_val!=rs2_val) {
                value=pc+imm;
            }
        } else if (op == "bltu") {

        } else if (op == "bne") {

        } else if (op == "jal") {

        } else if (op == "jalr") {

        } else if (op == "auipc") {

        } else if (op == "lui") {

        } else if (op == "ebreak") {

        } else if (op == "ecall") {

        } else if (op == "mul") {

        } else {
            std::cout<<"unknown instruction"<<std::endl;
            return calculate{};
        }
        return *this;
    }
};


#endif //ALUS_H
