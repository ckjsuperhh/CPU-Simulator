#include "RS.h"

#include "Rob.h"
//
// Created by ckjsuperhh6602 on 25-7-24.
//
inline bool busy_a[2] = {};
inline bool busy_l[2] = {};
inline bool busy_j[2] = {};//0-空闲,1-忙碌
std::string op[6];
  int Vj[6]{};
  int Vk[6]{};
  int Qj[6]{};
  int Qk[6]{};
  int A[6]{};
  Pos pk[6]{};
Pos pj[6]{};//这两个数组是为了在广播的时候，修改到ROB内部我知道应该修改rs1还是rs2而不需要再做讨论
int Dest[6]{};//0,1-load;2,3-add;4,5-jump
//不需要返回值，因为通过ins被修改的状态就可以窥见是否成功launch了
int RS::launch(inst &ins, const int i) {
    //在RS里边写读取寄存器的逻辑,所以传引用进来便于修改
    //先查找是否有空闲的档位
    if (load.contains(ins.op)) {
        if (!busy_l[0]) {
            ins.st=Issue;
            busy_l[0]=true;
            op[0]=ins.op;
            Dest[0]=i;
            Read_regs::execute(ins,Vj[0],Vk[0],Qj[0],Qk[0],pj[0],pk[0]);//读取Reg的值,并且修改RS表
            return 0;
        }else if (!busy_l[1]) {
            ins.st=Issue;
            busy_l[1]=true;
            op[1]=ins.op;
            Dest[1]=i;
            Read_regs::execute(ins,Vj[1],Vk[1],Qj[1],Qk[1],pj[1],pk[1]);
            return 1;
        }else {
            return -1;//没有空闲的档位.不做调整
        }
    }else if (add.contains(ins.op)) {
        if (!busy_a[0]) {
            ins.st=Issue;
            busy_a[0]=true;
            op[2]=ins.op;
            Dest[2]=i;
            Read_regs::execute(ins,Vj[2],Vk[2],Qj[2],Qk[2],pj[2],pk[2]);//读取Reg的值,并且修改RS表
            return 2;
        }else if (!busy_a[1]) {
            ins.st=Issue;
            busy_a[1]=true;
            op[3]=ins.op;
            Dest[3]=i;
            Read_regs::execute(ins,Vj[3],Vk[3],Qj[3],Qk[3],pj[3],pk[3]);
            return 3;
        }else {
            return -1;//没有空闲的档位.不做调整
        }
    }else if (jump.contains(ins.op)){
        if (!busy_j[0]) {
            ins.st=Issue;
            busy_j[0]=true;
            op[4]=ins.op;
            Dest[4]=i;
            Read_regs::execute(ins,Vj[4],Vk[4],Qj[4],Qk[4],pj[4],pk[4]);//读取Reg的值,并且修改RS表
            return 4;
        }else if (!busy_j[1]) {
            ins.st=Issue;
            busy_j[1]=true;
            op[5]=ins.op;
            Dest[5]=i;
            Read_regs::execute(ins,Vj[5],Vk[5],Qj[5],Qk[5],pj[5],pk[5]);
            return 5;
        }else {
            return -1;//没有空闲的档位.不做调整
        }
    }
    return -1;
};

void RS::clear(const int i) {//把第i行对应指令删除
    if (i<0||i>=6) {
        std::__throw_runtime_error("ops!");
    }
    if (i==0||i==1) {//删除load指令
        busy_l[i]=false;
    }else if (i==2||i==3) {
        busy_a[i-2]=false;
    }else {
        busy_j[i-4]=false;
    }
    op[i]="";
    Dest[i]=A[i]=Vj[i]=Vk[i]=Qj[i]=Qk[i]=-1;
    pj[i]=pk[i]=none;
}
