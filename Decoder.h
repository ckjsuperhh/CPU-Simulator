//
// Created by ckjsuperhh6602 on 25-7-21.
//

#ifndef DECODER_H
#define DECODER_H
#include <iomanip>
#include <iostream>

inline void decoder(const __uint32_t ins, std::string &op, int &rd, int &rs1, int &rs2, int &imm, std::string& type) {
    unsigned int imm_11_5;
    unsigned int imm_4_0;
    unsigned int imm_12 ;
    unsigned int imm_10_5 ;
    unsigned int imm_4_1 ;
    unsigned int imm_11 ;
    unsigned int imm_20 ;
    unsigned int imm_10_1 ;
    unsigned int imm_11_ ;
    unsigned int imm_19_12 ;
    switch (const auto opcode = ins & 127; opcode) {
        case 0b0110011:
            type = "R";
            rd = (ins >> 7) & 15;
            rs1 = (ins >> 15) & 15;
            rs2 = (ins >> 20) & 15;
            switch (const auto funct3 = (ins >> 12) & 7; funct3) {
                case 0b000:
                    switch (const auto funct7 = (ins >> 25) & 127; funct7) {
                        case 0b0000000:
                            op = "add";
                            break;
                        case 0b0100000:
                            op = "sub";
                            break;
                        default:
                            op = "uk";
                            break;
                    }
                case 0b111:
                    op = "and";
                    break;
                case 0b110:
                    op = "or";
                    break;
                case 0b100:
                    op = "xor";
                    break;
                case 0b001:
                    op = "sll";
                    break;
                case 0b101:
                    switch (const auto funct7 = (ins >> 25) & 127; funct7) {
                        case 0b0000000:
                            op = "srl";
                            break;
                        case 0b0100000:
                            op = "sra";
                            break;
                        default:
                            op = "uk";
                    }
                    break;
                case 0b010:
                    op = "slt";
                    break;
                case 0b011:
                    op = "sltu";
                    break;
                default: op = "uk";
            }
            break;
        case 0b0010011:
            type = "I";
            imm = (ins >> 20) & 0xFFF;
            rs1 = (ins >> 15) & 0x1F;
            rd = (ins >> 7) & 0x1F;
            switch (const auto funct3 = (ins >> 12) & 7; funct3) {
                case 0b000:
                    op = "addi";
                    break;
                case 0b111:
                    op = "andi";
                    break;
                case 0b110:
                    op = "ori";
                    break;
                case 0b100:
                    op = "xori";
                    break;
                case 0b001:
                    type = "I*";
                    op = "slli";
                    imm = (ins >> 20) & 0x1F;
                    break;
                case 0b101:
                    switch (const auto funct7 = (ins >> 25) & 127; funct7) {
                            type = "I*";
                            imm = (ins >> 20) & 0x1F;
                        case 0b0000000:
                            op = "srli";
                            break;
                        case 0b0100000:
                            op = "srai";
                            break;
                        default:
                            op = "uk";
                    }
                    break;
                case 0b010:
                    op = "slti";
                    break;
                case 0b011:
                    op = "sltiu";
                    break;
                default:
                    op = "uk";
            }
            break;
        case 0b0000011:
            type = "I";
            imm = (ins >> 20) & 0xFFF;
            rs1 = (ins >> 15) & 0x1F;
            rd = (ins >> 7) & 0x1F;
            switch (const auto funct3 = (ins >> 12) & 7; funct3) {
                case 0b000:
                    op = "lb";
                    break;
                case 0b100:
                    op = "lbu";
                    break;
                case 0b001:
                    op = "lh";
                    break;
                case 0b101:
                    op = "lhu";
                    break;
                case 0b010:
                    op = "lw";
                    break;
                default:
                    op = "uk";
            }
            break;
        case 0b0100011:
            type = "S";
            imm_11_5 = (ins >> 25) & 0x7F; // [31:25]
            rs2 = (ins >> 20) & 0x1F;
            rs1 = (ins >> 15) & 0x1F;
            imm_4_0 = (ins >> 7) & 0x1F; // [11:7]
            imm = (imm_11_5 << 5) | imm_4_0;
            switch (const auto funct3 = (ins >> 12) & 7; funct3) {
                case 0b000:
                    op = "sb";
                    break;
                case 0b001:
                    op = "sh";
                    break;
                case 0b010:
                    op = "sw";
                    break;
                default:
                    op = "uk";
            }
            break;
        case 0b1100011:
            type = "B";
            imm_12 = (ins >> 31) & 1;
            imm_10_5 = (ins >> 25) & 0x3F;
            rs2 = (ins >> 20) & 0x1F;
            rs1 = (ins >> 15) & 0x1F;
            imm_4_1 = (ins >> 8) & 0xF;
            imm_11 = (ins >> 7) & 1;
            imm = (imm_12 << 12) | (imm_11 << 11) | (imm_10_5 << 5) | (imm_4_1 << 1);
            switch (const auto funct3 = (ins >> 12) & 7; funct3) {
                case 0b000:
                    op = "beq";
                    break;
                case 0b101:
                    op = "bge";
                    break;
                case 0b111:
                    op = "bgeu";
                    break;
                case 0b100:
                    op = "blt";
                    break;
                case 0b110:
                    op = "bltu";
                    break;
                case 0b001:
                    op = "bne";
                    break;
                default:
                    op = "uk";
            }
            break;
        case 0b1101111:
            type = "J";
            imm_20 = (ins >> 31) & 1;
            imm_10_1 = (ins >> 21) & 0x3FF;
            imm_11_ = (ins >> 20) & 1;
            imm_19_12 = (ins >> 12) & 0xFF;
            rd = (ins >> 7) & 0x1F;
            imm = (imm_20 << 20) | (imm_19_12 << 12) | (imm_11_ << 11) | (imm_10_1 << 1);
            op = "jal";
            break;
        case 0b1100111:
            type = "I";
            imm = (ins >> 20) & 0xFFF;
            rs1 = (ins >> 15) & 0x1F;
            rd = (ins >> 7) & 0x1F;
            switch (const auto funct3 = (ins >> 12) & 7; funct3) {
                case 0b000:
                    op = "jalr";
                    break;
                default:
                    op = "uk";
            }
            break;
        case 0b0010111:
            type = "U";
            imm = (ins>>12) & 0xFFFFF;
            rd = (ins >> 7) & 0x1F;
            op = "auipc";
            break;
        case 0b0110111:
            type = "U";
            imm = (ins>>12) & 0xFFFFF;
            rd = (ins >> 7) & 0x1F;
            op = "lui";
            break;
        case 0b1110011:
            type = "I";
            imm = (ins >> 20) & 0xFFF;
            rs1 = (ins >> 15) & 0x1F;
            rd = (ins >> 7) & 0x1F;
            switch (imm) {
                case 0:
                    op = "ebreak";
                    break;
                case 1:
                    op = "ecall";
                    break;
                default:
                    op = "uk";
            }
            break;
        default:
            op = "uk";
            break;
    }
}

class instructions {
public:
    __uint32_t instruction;
    std::string op;
    int pc;
    int rd, rs1, rs2, imm;
    std::string type;

    explicit instructions(const __uint32_t ins,const int pc) :instruction(ins), pc(pc), rs2(0), imm(0) {
        decoder(ins, op, rd, rs1, rs2, imm, type);
    }


    void show() const {
        std::cout << std::setfill('0') << std::setw(8) << std::hex << instruction;
        for (int i = 0; i < 12; i++) {
            std::cout << " ";
        }
        if (type == "R") {
            std::cout << op << " " << trans_reg(rd) << " " << trans_reg(rs1) << " " << trans_reg(rs2) << std::endl;
        } else if (type == "S") {
            std::cout << op << " " << trans_reg(rs2) << " " << trans_imm(imm) << "(" << trans_reg(rs1) << ")" << std::endl;
        } else if (type == "B") {
            std::cout << op << " " << trans_reg(rs1) << " " << trans_reg(rs2) << " " << trans_imm(imm) << std::endl;
        } else if (type == "U" || op == "jal") {
            std::cout << op << " " << trans_reg(rd) << " " << imm << std::endl;
        } else if (op == "ebreak" || op == "ecall") {
            std::cout << op << std::endl;
        } else if (op == "jalr") {
            std::cout << op << " " << trans_reg(rd) << " " << trans_reg(rs1) << " " << imm << std::endl;
        } else if (op == "lb" || op == "lbu" || op == "lh" || op == "lhu" || op == "lw") {
            std::cout << op << " " << trans_reg(rd) << " " << trans_imm(imm) << "(" << trans_reg(rs1) << ")" << std::endl;
        } else {
            std::cout << op << " " << trans_reg(rd) << " " << trans_reg(rs1) << " " << trans_imm(imm) << std::endl;
        }
    }

    static std::string trans_reg(const int reg) {
        std::string reg_num[]{"zero","ra","sp","gp","tp","t0","t1","t2","s0","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6"};
        if (reg>=32) {
            return "uk";
        }
        return reg_num[reg];
    }
    static std::string trans_imm(const int imm) {
        std::ostringstream oss;
        oss << imm;  // 流默认是十进制格式
        return oss.str();
    }
};
#endif //DECODER_H
