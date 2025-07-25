//
// Created by ckjsuperhh6602 on 25-7-22.
//

#ifndef LSB_H
#define LSB_H
#include <map>

enum Op {
    nothing,read,write
};
class LSB {
//这不是一个static的类，需要生成一个又一个的对象，然后我要做的就是把这些对象按照先进先出的队列方式运行
public:
    bool ready{};//那么这个时候就涉及到怎么修改队列中的对象，所以更好的方法应该是一个有序的map而不是队列，这样就可以根据counter给出的索引进行查询，而需要运行就把begin拿出来，观察是否可以运行
    ticker_mem m{};
    std::string op{};
    Op rw{};
    bool execute() {//我觉得在内部封装可能是一个更可行的事情
        if (rw==write) {
            if (m.write()) {//如果进行存取成功，那么就把这一个清除掉(传true出去，外部要把begin删掉)，不然就只是ticker往后走了一位



                return true;
            }
        }else if (rw==read) {
            if (m.read()) {



                return true;
            }
        }
        return false;
    }//还需要考虑的就是LSB怎么和ROB_Table中的指令进行互动
};
    class LSB_seq {
        /*
         * 重点就是数据在计算出来之后，我应该维护内存读写的一个顺序性
         * 有个初步的想法，就是写一个并非static的类，每个都是一个对象，然后再由一个统一的标准进行排序和赋值
         * 无论如何，指令肯定是先读入比后读入要早，那么就可以在加入ROB的时候进行赋值
         */
    public:
        static int counter;
        static std::map<int,LSB> cnt_LSB;//一个编号对应一个LSB
        static void execute() {
            if (cnt_LSB.empty()) {//空的就不执行
                return;
            }
            if (cnt_LSB.begin()->second.execute()) {//反正进行一步，如果能进行就进行，否则就不进行
                cnt_LSB.erase(cnt_LSB.begin()->first);
            }
        }
        static void modify() {//当我需要对其进行修改的时候(需要明确修改什么)

        }
        static void add() {//当decode完加入ROB的时候，我就应该把对应的LSB加入map中

        }
    };

inline int counter=0;
#endif //LSB_H
