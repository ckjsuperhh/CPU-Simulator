//
// Created by ckjsuperhh6602 on 25-7-24.
//
#include "Ins_Cache.h"
#include "rob.h"
#include "RS.h"
std::unordered_set<std::string> read_mem = {"lb", "lbu", "lh", "lhu", "lw"};
std::unordered_set<std::string> write_mem ={ "sb","sh","sw"};
std::unordered_set<std::string> double_reg ={"add","sub","and","or","xor","sll","srl","sra","slt","sltu","sb","sh","sw","beq","bge","bgeu","blt","bltu","bne"};
std::unordered_set<std::string> first_reg ={"jalr","addi","andi","ori","xori","slli","srli","srai","slti","sltiu","lb","lbu","lh","lhu","lw"};
std::unordered_set<std::string> only_pc={"jal","auipc","lui"};
std::unordered_set<std::string> load={"lb","lbu","lh","lhu","lw","sb","sh","sw",};
std::unordered_set<std::string> add={"add","sub","and","or","xor","sll","srl","sra","slt","sltu","addi","andi","ori","xori","slli","srli","srai","slti","sltiu"};
std::unordered_set<std::string> jump={"beq","bge","bgeu","blt","bltu","bne","jal","jalr","auipc","lui","ebreak","ecall"};
int ROB::head = 0;
int ROB::tail = 1;
inst ROB::ROB_Table[10000]{};
int ROB::code[10000]{};

// inst构造函数实现（如果函数体不复杂，可以写在struct里，否则习惯性单独写）
inst::inst(const instructions& a)
    :op(a.op), pc(a.pc),rd(a.rd), rs1(a.rs1), rs2(a.rs2), imm(a.imm), st(Decoded) {}

// 静态成员函数实现
bool ROB::execute() {
    bool end = true;
    for (int i = head; i <= tail; i++) {
        if (ROB_Table[i].st == Decoded) {//准备发射,先看RS里边有没有适合的空位,再从reg中读值(两步都应该在这边干)
            code[i]=RS::launch(ROB_Table[i],i);
        } else if (ROB_Table[i].st == Issue) {
            if (RS::Qj[code[i]]==-1&&RS::Qk[code[i]]==-1) {//数据已经做好准备,可以ALUs伺候

            }//否则就等待数据全部都准备好了
        } else if (ROB_Table[i].st == Exec) {//运行完观察是否要写回Reg和内存
            if () {
                end = false;
            }
        } else if (ROB_Table[i].st == Write) {//读写内存和寄存器





            head++;
        } else {
            if (ROB_Table[i].st == None) {//还没有载入语句
                if (!Ins_Cache::cache.empty()) {//如果非空就可以载入一条指令，由于是最后在None的位置载入，所以jump指令的处理必定会在载入之前，可以及时封存载入(clear掉)
                        const auto t=Ins_Cache::read();
                    ROB_Table[i].pc=t.second;
                    ROB_Table[i].ins=t.first;
                    tail++;
                    Register::pc=ROB_Table[i].pc;//当且仅当载入的时候正常修改pc,其他可能会修改pc的情况仅仅存在于ALU
                }
            }else {//需要进行Decode(一般只要能够到这一步,都是可以运行并且准备发布的)
                if (instructions ins(ROB_Table[i].ins,ROB_Table[i].pc); ins.op=="uk") {
                    //我也不知道应该怎么办
                }else {
                    ROB_Table[i]=inst{ins};//Decode完成之后,我需要准备开始发射了
                }
            }
        }
    }
    return end;
}