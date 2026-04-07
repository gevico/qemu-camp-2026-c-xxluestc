#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge(int left, int mid, int right) {
    int i = left;      // 左半部分的起始索引
    int j = mid + 1;   // 右半部分的起始索引
    int k = left;      // 临时数组 temp 的索引

    // 比较两个部分的元素，将成绩大的（从高到低）先放入 temp
    while (i <= mid && j <= right) {
        if (students[i].score >= students[j].score) {
            temp[k++] = students[i++];
        } else {
            temp[k++] = students[j++];
        }
    }

    // 如果左边还有剩余，全部搬过去
    while (i <= mid) {
        temp[k++] = students[i++];
    }

    // 如果右边还有剩余，全部搬过去
    while (j <= right) {
        temp[k++] = students[j++];
    }

    // 把排序好的临时数组拷回原数组 students
    for (int p = left; p <= right; p++) {
        students[p] = temp[p];
    }
}

void merge_sort(int left, int right) {
    // TODO: 在这里添加你的代码
    // 递归终止条件：当区间只有一个元素时，不需要再分了
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 分：递归处理左半边和右半边
        merge_sort(left, mid);
        merge_sort(mid + 1, right);

        // 治：合并两个有序序列
        merge(left, mid, right);
    }
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}