//
// Created by ckjsuperhh6602 on 25-7-24.
//

#ifndef CDB_H
#define CDB_H
#include <map>
#include <unordered_map>
#include <bits/types.h>

#include "RS.h"

enum Pos {
    RS,RF,Mem,Rob
};
class CDB {//广播之后需要把RS和ROB中的相关值进行修改，保证RS我可以判断值是否准备好了，而ROB_Table中的inst的reg_val修改掉
public:
    static std::map<int,int> update;//ROB_TABLE的编号对应修改的数据，肯定是从早到晚
    static void execute() {
        if (update.size()>=2) {//一次选两个数据进行通报
            int i=0;
            int first_node,second_node;
            for (auto it=update.begin();it!=update.end();++i,++it) {
                if (i==2) {
                    break;
                }
                if (i==0) {
                    first_node=it->first;
                    broadcast(it->first,it->second);
                }
                if (i==1) {
                    second_node=it->first;
                    broadcast(it->first,it->second);
                }
            }
            update.erase(first_node);
            update.erase(second_node);

        }else if (update.size()==1) {
            const auto it=update.begin();
            broadcast(it->first,it->second);
            update.clear();
        }
        //空的直接不做广播
    }

    static void add(int i,int data) {
        update.emplace(i,data);
    }

    static void broadcast(int i,int value) {
        for (int j=0;j<2;j++) {
            if (RS::busy_l[j]==1) {
                if (RS::Vj[j]==-1&&RS::Qj[j]==i) {
                    RS::Qj[j]=-1;
                    RS::Vj[j]=value;
                    if (RS::pj[j]==rs1) {
                        ROB::ROB_Table[RS::Dest[j]].rs1_val=value;
                    }else if (RS::pj[j]==rs1){
                        ROB::ROB_Table[RS::Dest[j]].rs2_val=value;
                    }
                }
                if (RS::Vk[j]==-1&&RS::Qk[j]==i) {
                    RS::Qk[j]=-1;
                    RS::Vk[j]=value;
                    if (RS::pk[j]==rs1) {
                        ROB::ROB_Table[RS::Dest[j]].rs1_val=value;
                    }else if (RS::pk[j]==rs1){
                        ROB::ROB_Table[RS::Dest[j]].rs2_val=value;
                    }
                }
            }
            if (RS::busy_a[j]==1) {
                if (RS::Vj[j+2]==-1&&RS::Qj[j+2]==i) {
                    RS::Qj[j+2]=-1;
                    RS::Vj[j+2]=value;
                    if (RS::pj[j+2]==rs1) {
                        ROB::ROB_Table[RS::Dest[j+2]].rs1_val=value;
                    }else if (RS::pj[j+2]==rs1){
                        ROB::ROB_Table[RS::Dest[j+2]].rs2_val=value;
                    }
                }
                if (RS::Vk[j+2]==-1&&RS::Qk[j+2]==i) {
                    RS::Qk[j+2]=-1;
                    RS::Vk[j+2]=value;
                    if (RS::pk[j+2]==rs1) {
                        ROB::ROB_Table[RS::Dest[j+2]].rs1_val=value;
                    }else if (RS::pk[j+2]==rs1){
                        ROB::ROB_Table[RS::Dest[j+2]].rs2_val=value;
                    }
                }
            }
            if (RS::busy_j[j]==1) {
                if (RS::Vj[j+4]==-1&&RS::Qj[j+4]==i) {
                    RS::Qj[j+4]=-1;
                    RS::Vj[j+4]=value;
                    if (RS::pj[j+4]==rs1) {
                        ROB::ROB_Table[RS::Dest[j+4]].rs1_val=value;
                    }else if (RS::pj[j+4]==rs1){
                        ROB::ROB_Table[RS::Dest[j+4]].rs2_val=value;
                    }
                }
                if (RS::Vk[j+4]==-1&&RS::Qk[j+4]==i) {
                    RS::Qk[j+4]=-1;
                    RS::Vk[j+4]=value;
                    if (RS::pk[j+4]==rs1) {
                        ROB::ROB_Table[RS::Dest[j+4]].rs1_val=value;
                    }else if (RS::pk[j+4]==rs1){
                        ROB::ROB_Table[RS::Dest[j+4]].rs2_val=value;
                    }
                }
            }
        }
    }
};
#endif //CDB_H
