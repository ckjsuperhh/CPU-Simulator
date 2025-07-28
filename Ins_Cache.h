//
// Created by ckjsuperhh6602 on 25-7-25.
//

#ifndef INS_CACHE_H
#define INS_CACHE_H
#include <queue>

#include "Memory.h"
#include "Rob.h"

enum Status{
    NONE,WAITING,FINISHED,LAST_READ,UNABLED
};//如果快要用完就重新读取一堆,所以我只设置这五个状态,倒数第二个状态就是承接UNABLED的最后一次读入,最后一个状态表示已经读到最后没办法再往后了
class Ins_Cache {
public:
    static Status st;
    static int pc;
    static std::queue<std::pair<ticker_mem,int>> cache_mem;
    static std::queue<std::pair<__uint32_t,int>> cache;//读出来的时候大不了用这个queue是否为空来判断能否读取
    static std::pair<__uint32_t,int> read() {//读取最近的一条指令
        auto tmp=cache.front();
        cache.pop();
        return tmp;
    }
    static bool empty() {//规范用法，读取之前先要判空
        return cache.empty();
    }
    static void clear(const int _pc) {//涉及清除指令，应该都是jump要更改pc的时候，那么就传入pc允许修改
        pc=_pc;
        while (!cache.empty()) {
            cache.pop();
        }
        while (!cache_mem.empty()) {
            cache_mem.pop();
        }
        st=NONE;//这样设置之后,从下回合开始就会主动设计重读(check的优秀功能)
    }
    static void check() {
        //每回合的clock里边应该调用的东西
        if (st==UNABLED) {
            return;//如果读到最后，那再往后读也没什么意义，所以不管
        }

        if (st==NONE) {
            for (int i=0;i<8;++i,pc+=4) {//用了一些奇技淫巧，如果pc加完之后，内存读不出来东西，说明读到头了
                if (Memory::read4(pc)!=0){//不会有指令是全0吧,那么这边就用于判错
                    st=LAST_READ;
                    break;
                }
                cache_mem.emplace(ticker_mem(pc),pc);
            }
            if (st!=LAST_READ) {
                st=WAITING;
            }
        }else if (st==WAITING) {
            bool ok=false;
            std::vector<std::pair<ticker_mem,int>> tmp;
            while (!cache_mem.empty()) {
                tmp.push_back(cache_mem.front());
                cache_mem.pop();
                ok=tmp.back().first.read4();
            }
            if (ok) {
                for (auto &[fst, snd]:tmp ) {
                    cache.emplace(Binary_Little_Endian(std::to_string(fst.val).data()),snd);
                }//读取成功之后就直接写到缓存中
                st=FINISHED;
            }else {
                for (auto & it : tmp) {
                    cache_mem.push(it);
                }
            }
        }else if (st==LAST_READ) {
            bool ok=false;
            std::vector<std::pair<ticker_mem,int>> tmp;
            while (!cache_mem.empty()) {
                tmp.push_back(cache_mem.front());
                cache_mem.pop();
                ok=tmp.back().first.read4();
            }
            if (ok) {
                for (auto &[fst, snd]:tmp ) {
                    cache.emplace(fst.val,snd);
                }//读取成功之后就直接写到缓存中
                st=UNABLED;
            }else {
                for (auto & it : tmp) {
                    cache_mem.push(it);
                }
            }
        }else if (st==FINISHED) {//逻辑是这样，只有load完成八条想要再往后的才可能会被<=3命中
            if (cache.size()<=3) {//如果发现剩余存量不足3(正好后续时间只够load三条语句)
                bool hit_last_read = false;
                for (int i=0;i<8-cache.size();++i,pc+=4) {
                    if (Memory::read4(pc)!=0){
                        hit_last_read = true;
                        break;
                    }
                    cache_mem.emplace(ticker_mem(pc),pc);
                }
                if (!hit_last_read) {
                    st=WAITING;
                } else {
                    st=LAST_READ;
                }
            }
        }
    }
};



#endif //INS_CACHE_H
