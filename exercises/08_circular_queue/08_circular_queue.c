#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // 初始化队列
    q.head = 0;
    q.tail = 0;
    q.count = 0;
    
    // 将 50 个人依次入队
    for (int i = 0; i < total_people; i++) {
        q.data[q.tail].id = i + 1;
        q.tail = (q.tail + 1) % MAX_PEOPLE;
        q.count++;
    }
    
    // 约瑟夫环：报到 report_interval 的人出队
    while (q.count > 1) {
        // 将前 report_interval-1 个人依次出队再入队
        for (int i = 0; i < report_interval - 1; i++) {
            People p = q.data[q.head];
            q.head = (q.head + 1) % MAX_PEOPLE;
            q.count--;
            
            // 出队的人重新入队
            q.data[q.tail] = p;
            q.tail = (q.tail + 1) % MAX_PEOPLE;
            q.count++;
        }
        
        // 第 report_interval 个人出队（淘汰）
        printf("淘汰: %d\n", q.data[q.head].id);
        q.head = (q.head + 1) % MAX_PEOPLE;
        q.count--;
    }
    
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}