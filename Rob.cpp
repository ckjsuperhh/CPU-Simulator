//
// Created by ckjsuperhh6602 on 25-7-24.
//
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
    : op(a.op),rd(a.rd), rs1(a.rs1), rs2(a.rs2), imm(a.imm), st(Decoded) {}

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
            if (read_mem.contains(i)) {
                if (read_mem.contains(i)) {
                    read_mem[i].read();
                }
                if () {
                    Read_regs(ROB_Table[i]).execute(TODO, TODO, TODO, TODO, TODO, TODO, TODO);
                }
            } else {
                // 其他处理
            }
            head++;
        } else {
            if (ROB_Table[i].st == None) {//还没有载入语句
                if (ROB_Table[i].pc==-1) {//没有进行过载入或者没有载入成功
                    ROB_Table[i].pc=Register::read_pc();
                }else {//载入成功
                    if (read_mem.contains(i)) {//判断这条语句有没有进入过内存访问存储
                        if (read_mem[i].read()) {//只有已经加进去才有可能读到三次
                            ROB_Table[i].ins=read_mem[i].reg_val;//读出来的新鲜出炉的指令(32位二进制)
                            ROB_Table[i].st=Waiting;//进入等待站等待decode
                            read_mem.erase(i);//把这个内存清除掉
                            tail++;

                        }
                    }else {
                        read_mem.emplace(i,ticker_mem(ROB_Table[i].pc));//读取pc对应的指令是什么
                        read_mem[i].read();
                    }
                }
            }else {//需要进行Decode(一般只要能够到这一步,都是可以运行并且准备发布的)
                if (instructions ins(ROB_Table[i].ins); ins.op=="uk") {
                    //我也不知道应该怎么办
                }else {
                    ROB_Table[i]=inst{ins};//Decode完成之后,我需要准备开始发射了
                }
            }
        }
    }
    return end;
}