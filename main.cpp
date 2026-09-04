#include<stdio.h>
#include<stdlib.h>
typedef struct QNode {
    int data;
    struct QNode* next;
}QNode;
typedef struct LineQueue {
    QNode* front;
    QNode* rear;
}LineQUeue;
void InQueue(LineQueue* q) {
    q->front = (QNode*)malloc(sizeof(QNode));
    if (!q->front) {
        printf("内存分配失败！");
        exit(-1);
    }
    q->rear = q->front;
    q->rear->next = NULL;
}
int Enqueue(LineQueue* q, int e) {
    QNode* p = (QNode*)malloc(sizeof(QNode));
    if (!p) {
        printf("内存不足，入队失败！");
        return 0;
    }
    p->data = e;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
    return 1;
}
int Dequeue(LineQueue* q, int* e) {
    if (q->front == q->rear) {
        printf("队列为空，无法出列！");
        return 0;
    }
    QNode* p = q->front->next;
    *e = p->data;
    q->front->next = p->next;
    if (q->rear == p) {
        q->rear = q->front;
    }
    free(p);
    return 1;
}
void Printqueue(LineQueue q) {
    if (q.front == q.rear) {
        printf("队列为空，无元素！");
        return;
    }
    QNode* p = q.front->next;
    printf("队列元素！");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int Getqueue(LineQueue q) {
    int len = 0;
    QNode* p = q.front->next;
    while (p != NULL) {
        len++;
        p = p->next;
    }
    return len;
}
void Clearqueue(LineQueue* q) {
    QNode* p = q->front->next;
    while (p != NULL) {
        QNode* temp = p;
        p = p->next;
        free(temp);
    }
    q->rear = q->front;
    q->front->next = NULL;
    printf("队列已清空\n");
}
int Searqueue(LineQueue q, int x) {
    QNode* p = q.front->next;
    while (p != NULL) {
        if (p->data == x) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}
void Menu() {
    printf("\n==========链表操作系统==========\n");
    printf("1.入队操作\n");
    printf("2.出队操作\n");
    printf("3.输出队列所以元素\n");
    printf("4.求队列长度\n");
    printf("5.清空队列(置空)\n");
    printf("6.查找指定数值\n");
    printf("0.退出系统\n");
    printf("================================\n");
    printf("请输入功能序号");
}
int main() {
    LineQueue q;
    InQueue(&q);
    int choice, val, res, x;
    while (1) {
        Menu();
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            printf("请输入要入队的整数:");
            scanf_s("%d", &val);
            Enqueue(&q, val);
            printf("入队成功！\n");
            break;
        case 2:
            if (Dequeue(&q, &res)) {
                printf("出队元素为:%d", res);
            }
            break;
        case 3:
            Printqueue(q);
            break;
        case 4:
            printf("当前队列长度:%d\n", Getqueue(q));
            break;
        case 5:
            Clearqueue(&q);
            break;
        case 6:
            printf("请输入要查找的值:");
            scanf_s("%d", &x);
            if (Searqueue(q, x)) {
                printf("查找成功，队列中存在%d\n", x);
            }
            else {
                printf("查找失败，队列无%d\n", x);
            }
            break;
        case 0:
            Clearqueue(&q);
            free(q.front);
            printf("队列资源释放完毕，程序退出\n");
            return 0;
        default:
            printf("输入序号错误，请重新选择！\n");
        }

    }
    return 0;
}