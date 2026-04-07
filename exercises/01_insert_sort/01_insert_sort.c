#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score;
} Student;

void insertion_sort(Student students[], int n) {
    // TODO: 在这里添加你的代码
    for (int i = 1; i < n; i++) {
        // 1. 选出当前待排序的学生（“抓起一张牌”）
        Student key = students[i];
        int j = i - 1;

        /* * 2. 将 key.score 与前面的学生成绩进行比较
         * 因为是要“从高到低”，所以如果前面的成绩比 key 小，就后移
         */
        while (j >= 0 && students[j].score < key.score) {
            students[j + 1] = students[j];
            j--;
        }

        // 3. 将 key 插入到腾出的空位
        students[j + 1] = key;
    }
}

int main(void) {
    FILE *file;
    Student students[50];
    int n = 0;
    
    // 打开文件（从命令行参数获取文件名）
    file = fopen("01_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 01_students.txt\n");
        return 1;
    }
    
    // 从文件读取学生信息
    while (n < 50 && fscanf(file, "%s %d", students[n].name, &students[n].score) == 2) {
        n++;
    }
    fclose(file);
    
    if (n == 0) {
        printf("文件中没有学生信息\n");
        return 1;
    }
    
    insertion_sort(students, n);
    
    printf("\n按成绩从高到低排序后的学生信息:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }
    
    return 0;
}

