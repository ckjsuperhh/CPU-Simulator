//
// Created by ckjsuperhh6602 on 25-7-24.
//
#include "ALUs.h"
#include "CDB.h"
#include "Ins_Cache.h"
#include "LSB.h"
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

// inst构造函数实现
inst::inst(const instructions& a)
    :i(-1),op(a.op), pc(a.pc),rd(a.rd), rs1(a.rs1), rs2(a.rs2), imm(a.imm), st(Decoded) {}

// 静态成员函数实现
bool ROB::execute() {
    bool end=false;
    bool end_of_ALU=false;
    bool end_of_Commit=false;
    bool end_of_LSB=false;
    for (int i = head; i <= tail; i++) {
        if (ROB_Table[i].st == Decoded) {//准备发射,先看RS里边有没有适合的空位,再从reg中读值(两步都应该在这边干)
            code[i]=RS::launch(ROB_Table[i],i);
            end=true;
        } else if (ROB_Table[i].st == Issue) {
            if (!end_of_ALU&&RS::Qj[code[i]]==-1&&RS::Qk[code[i]]==-1) {//数据已经做好准备,可以ALUs伺候
                calculate::cal(ROB_Table[i]);//答案数据准备好了，注意这边似乎还没有处理pc相关的任务，后续再说吧
                ROB_Table[i].st=Exec;
                CDB::add(i,ROB_Table[i].value);//加入队列中准备进行一个数据的广播
                end_of_ALU=true;//一次只允许一次ALU工作
                end=true;
                if (!load.contains(ROB_Table[i].op)) {
                    RS::clear(code[i]);
                }else {//算出来地址之后,LSB的数据全部准备好了,我是不是可以进行修改了
                    if (ROB_Table[i].op=="sb") {
                        LSB_seq::modify(i,ROB_Table[i].value,0xFF&ROB_Table[i].rs2_val);
                    }else if (ROB_Table[i].op=="sh") {
                        LSB_seq::modify(i,ROB_Table[i].value,0xFFFF&ROB_Table[i].rs2_val);
                    }else if (ROB_Table[i].op=="sw") {
                        LSB_seq::modify(i,ROB_Table[i].value);
                    }else {
                        LSB_seq::modify(i,ROB_Table[i].value);
                    }
                }
                Reg_status::Busy_pc=false;//这一步结束之后,Busy_pc不再忙碌(由于之前的bubble逻辑，这行指令之后必定不会有任何指令的输入)
            }//否则就等待数据全部都准备好了
            //我发现好像这一步就可以清空对应的RS了，除了Load相关的指令以外，下一步都准备提交了
        } else if (ROB_Table[i].st == Exec) {//运行完观察是否要写回Reg和内存,这个时候就要分类是否与内存有关
            if (i==0) {//特判，因为没有上一条，可以直接运行
                if (add.contains(ROB_Table[i].op)) {
                    Write_regs::execute(i,ROB_Table[i].rd,ROB_Table[i].value);
                    ROB_Table[i].st=Commit;
                    head++;
                    end_of_Commit=true;
                }else if (load.contains(ROB_Table[i].op)) {//其他情况以后再进行尝试
                    if (!end_of_LSB) {
                        end_of_LSB=true;
                        if (LSB_seq::execute(ROB_Table[i].value)) {
                            if (ROB_Table[i].op=="sb"||ROB_Table[i].op=="sh"||ROB_Table[i].op=="sw") {//写完可以直接commit了
                                ROB_Table[i].st=Commit;
                            }else {
                                ROB_Table[i].st=Write;//从内存读出来之后我还需要把他放回寄存器
                            }
                            RS::clear(code[i]);
                        }
                    }
                }else {//剩下的jump指令还没有处理

                }
                //我应该修改寄存器，对应的值，这应该就够了
            }else {
                if (ROB_Table[i-1].st==Commit&&!end_of_Commit){//上一条必须是已经Commit过了并且这回合没有其他提交过
                    if (add.contains(ROB_Table[i].op)) {
                        Write_regs::execute(i,ROB_Table[i].rd,ROB_Table[i].value);
                        ROB_Table[i].st=Commit;
                        head++;
                        end_of_Commit=true;
                    }else if (load.contains(ROB_Table[i].op)) {
                        if (!end_of_LSB) {
                            end_of_LSB=true;
                            if (LSB_seq::execute(ROB_Table[i].value)) {
                                if (ROB_Table[i].op=="sb"||ROB_Table[i].op=="sh"||ROB_Table[i].op=="sw") {//写完可以直接commit了
                                    ROB_Table[i].st=Commit;
                                }else {
                                    ROB_Table[i].st=Write;//从内存读出来之后我还需要把他放回寄存器
                                }
                                RS::clear(code[i]);
                            }
                        }
                    }
                }
            }
            end=true;
        } else if (ROB_Table[i].st == Write) {//读写内存和寄存器,与LSB有关，我现在先不写
            if (i==0||(ROB_Table[i-1].st==Commit&&!end_of_Commit)) {
                Write_regs::execute(i,ROB_Table[i].rd,ROB_Table[i].value);
                ROB_Table[i].st=Commit;
                head++;
                end_of_Commit=true;
            }
            head++;
            end=true;
        } else {
            if (ROB_Table[i].st == None) {//还没有载入语句
                if (!Ins_Cache::cache.empty()&&!Reg_status::Busy_pc) {//如果非空就可以载入一条指令，由于是最后在None的位置载入，所以jump指令的处理必定会在载入之前，可以及时封存载入(clear掉),但我还是写上与Busy_pc相关的逻辑吧
                    const auto [fst, snd]=Ins_Cache::read();
                    ROB_Table[i].pc=snd;
                    ROB_Table[i].ins=fst;
                    tail++;
                    Register::pc=ROB_Table[i].pc;//当且仅当载入的时候正常修改pc,其他可能会修改pc的情况仅仅存在于ALU
                    end=true;
                }else if (!Ins_Cache::cache_mem.empty()||Ins_Cache::st==WAITING||Ins_Cache::st==LAST_READ) {//如果其他指令都不再运行了，但是还有指令没有导入，但是指令队列空了，那我应该还要特判一下
                    end=true;//如果等待读入的站还没空,或者还处在等待状态中,我就不能随意结束程序
                }
            }else {//需要进行Decode(一般只要能够到这一步,都是可以运行并且准备发布的)
                if (instructions ins(ROB_Table[i].ins,ROB_Table[i].pc); ins.op=="uk") {
                    //我也不知道应该怎么办
                }else {
                    const int pc=ROB_Table[i].pc;//来个暗度陈仓
                    ROB_Table[i]=inst{ins};//Decode完成之后,我需要准备开始发射了
                    ROB_Table[i].pc=pc;
                    if (load.contains(ROB_Table[i].op)) {//特殊的需要加入LSB中
                        ROB_Table[i].i=LSB_seq::add(ROB_Table[i]);
                    }
                }
                end=true;
            }
        }
    }
    return end;
}