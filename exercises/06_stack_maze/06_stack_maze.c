#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

// 栈节点结构
typedef struct StackNode {
	int row, col;
	struct StackNode *next;
} StackNode;

// 栈结构
typedef struct {
	StackNode *top;
	int size;
} Stack;

// 初始化栈
void initStack(Stack *s) {
	s->top = NULL;
	s->size = 0;
}

// 入栈
void push(Stack *s, int row, int col) {
	StackNode *node = (StackNode *)malloc(sizeof(StackNode));
	node->row = row;
	node->col = col;
	node->next = s->top;
	s->top = node;
	s->size++;
}

// 出栈
int pop(Stack *s, int *row, int *col) {
	if (s->top == NULL) return 0;
	StackNode *node = s->top;
	*row = node->row;
	*col = node->col;
	s->top = node->next;
	s->size--;
	free(node);
	return 1;
}

// 栈是否为空
int isEmpty(Stack *s) {
	return s->top == NULL;
}

// 检查位置是否可走
int canMove(int row, int col, int visited[MAX_ROW][MAX_COL]) {
	if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL)
		return 0;
	if (maze[row][col] == 1)
		return 0;
	if (visited[row][col])
		return 0;
	return 1;
}

// 释放栈内存
void freeStack(Stack *s) {
	while (!isEmpty(s)) {
		StackNode *node = s->top;
		s->top = node->next;
		free(node);
	}
}

int main(void) {
	int visited[MAX_ROW][MAX_COL] = {0};
	Stack stack;
	Stack pathStack;
	initStack(&stack);
	initStack(&pathStack);

	// 从起点(0,0)开始
	push(&stack, 0, 0);
	visited[0][0] = 1;

	int endRow = MAX_ROW - 1;
	int endCol = MAX_COL - 1;
	int found = 0;

	// DFS遍历
	while (!isEmpty(&stack)) {
		int row, col;
		pop(&stack, &row, &col);
		push(&pathStack, row, col);

		// 到达终点
		if (row == endRow && col == endCol) {
			found = 1;
			break;
		}

		// 尝试四个方向：下、右、上、左
		int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		for (int i = 0; i < 4; i++) {
			int newRow = row + dirs[i][0];
			int newCol = col + dirs[i][1];
			if (canMove(newRow, newCol, visited)) {
				visited[newRow][newCol] = 1;
				push(&stack, newRow, newCol);
			}
		}
	}

	// 输出路径（从终点到起点）
	if (found) {
		while (!isEmpty(&pathStack)) {
			int row, col;
			pop(&pathStack, &row, &col);
			printf("(%d, %d)\n", row, col);
		}
	} else {
		printf("No path!\n");
	}

	// 释放栈
	freeStack(&stack);
	freeStack(&pathStack);

	return 0;
}