#include <stdio.h>
#define SIZE 6                       /* usable capacity = 5 */

typedef struct { int pid, remaining; } Process;

Process q[SIZE];
int front = 0, rear = 0;

int isEmpty() { return front == rear; }
int isFull()  { return (rear + 1) % SIZE == front; }

int enqueue(Process p) {
    if (isFull()) { printf("  Overflow: P%d cannot be added\n", p.pid); return 0; }
    rear = (rear + 1) % SIZE;        /* wraparound */
    q[rear] = p;
    return 1;
}

int dequeue(Process *out) {
    if (isEmpty()) { printf("  Underflow: queue is empty\n"); return 0; }
    front = (front + 1) % SIZE;      /* wraparound */
    *out = q[front];
    return 1;
}

void display() {
    printf("  Queue: ");
    if (isEmpty()) printf("(empty)");
    else {
        int i = front;
        while (i != rear) { i = (i + 1) % SIZE; printf("P%d ", q[i].pid); }
    }
    printf("  [front=%d rear=%d]\n", front, rear);
}

int main(void) {
    Process p, run;
    int burst[] = {0, 5, 3, 4, 2, 6, 3};

    printf("== Insert P1 to P5 ==\n");
    for (int i = 1; i <= 5; i++) {
        p.pid = i; p.remaining = burst[i];
        enqueue(p);
    }
    display();

    printf("== Try to insert P6 (queue full) ==\n");
    p.pid = 6; p.remaining = burst[6];
    enqueue(p);

    printf("== Execute and remove P1 ==\n");
    dequeue(&run);
    printf("  P%d executed and removed\n", run.pid);
    display();

    printf("== Insert P6 (rear wraps to 0) ==\n");
    enqueue(p);
    display();

    printf("\n== Round-Robin, quantum = 2 ==\n");
    int quantum = 2, clock = 0;
    while (!isEmpty()) {
        dequeue(&run);
        int t = run.remaining < quantum ? run.remaining : quantum;
        printf("  t=%2d: P%d runs %d", clock, run.pid, t);
        clock += t;
        run.remaining -= t;
        if (run.remaining > 0) {
            enqueue(run);
            printf(" -> back to queue (%d left)\n", run.remaining);
        } else {
            printf(" -> finished at t=%d\n", clock);
        }
    }

    printf("\n== Remove from empty queue ==\n");
    dequeue(&run);
    display();
    return 0;
}
