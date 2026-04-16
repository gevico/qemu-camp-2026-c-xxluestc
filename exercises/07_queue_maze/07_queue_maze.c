#include <stdio.h>
#include <stdbool.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    Point data[MAX_ROW * MAX_COL];
    int head;
    int tail;
} Queue;

void queue_init(Queue *q) {
    q->head = 0;
    q->tail = 0;
}

void queue_push(Queue *q, Point p) {
    q->data[q->tail++] = p;
}

Point queue_pop(Queue *q) {
    return q->data[q->head++];
}

bool queue_empty(Queue *q) {
    return q->head == q->tail;
}

int main(void)
{
    bool visited[MAX_ROW][MAX_COL] = {false};
    Point parent[MAX_ROW][MAX_COL];
    Queue q;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    bool found = false;

    queue_init(&q);
    Point start = {0, 0};
    Point end = {4, 4};

    queue_push(&q, start);
    visited[start.row][start.col] = true;

    // BFS
    while (!queue_empty(&q) && !found) {
        Point cur = queue_pop(&q);

        if (cur.row == end.row && cur.col == end.col) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.row + dr[i];
            int nc = cur.col + dc[i];

            if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL &&
                maze[nr][nc] == 0 && !visited[nr][nc]) {
                visited[nr][nc] = true;
                parent[nr][nc] = cur;
                Point next = {nr, nc};
                queue_push(&q, next);
            }
        }
    }

    if (!found) {
        printf("No path!\n");
        return 0;
    }

    // 从终点回溯到起点，输出路径
    Point path[MAX_ROW * MAX_COL];
    int path_len = 0;
    Point cur = end;

    while (!(cur.row == start.row && cur.col == start.col)) {
        path[path_len++] = cur;
        cur = parent[cur.row][cur.col];
    }
    path[path_len++] = start;

    // 输出路径（从终点到起点）
    for (int i = 0; i < path_len; i++) {
        printf("(%d, %d)\n", path[i].row, path[i].col);
    }

    return 0;
}