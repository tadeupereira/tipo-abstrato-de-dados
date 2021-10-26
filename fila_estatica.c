#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int value[MAX];
    int begin, end, used;
} queue;

queue *create(void) {
    queue *q = (queue *) malloc(sizeof(queue));
    q->begin = q->end = q->used = 0;
    return q;
}

void clear(queue *q) {
    free(q);
}

int empty(queue *q) {
    return (q->used == 0);
}

int full(queue *q) {
    return (q->used == MAX);
}

void enqueue(queue *q, int v) {
    /* aborta programa */
    if (full(q)) {
        printf("Capacidade da fila estourou.\n");
        exit(1);
    }

    q->value[q->end] = v;

    // q->end = q->end + 1 == MAX ? 0 : q->end + 1;
    q->end = (q->end + 1) % MAX;
    q->used++;
}

int dequeue(queue *q) {
    /* aborta programa */
    if (empty(q)) {
        printf("Fila vazia.\n");
        exit(1);
    }

    int v = q->value[q->begin];
    
    q->begin = (q->begin + 1) % MAX;
    q->used--;

    return v;
}

int first(queue *q) {
    /* aborta programa */
    if (empty(q)) {
        printf("Fila vazia.\n");
        exit(1);
    }

    int v = q->value[q->begin];

    return v;
}

void print_all(queue *q) {
    if (empty(q))
        printf("Fila vazia.\n");
    else {
        int begin = q->begin;
        for (int i = 0; i < q->used; i++) {
            printf("%d\n", q->value[begin]);
            begin = (begin + 1) % MAX;
        }
    }
}

int main() {

    queue *fila;
    fila = create();

    print_all(fila);

    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);
    enqueue(fila, 40);
    enqueue(fila, 50);
    // enqueue(fila, 60);

    if (full(fila)) {
        printf("MAIN - Fila cheia.\n");
    }

    printf("dequeue: %d\n", dequeue(fila));
    printf("dequeue: %d\n", dequeue(fila));

    enqueue(fila, 60);
    enqueue(fila, 70);

    printf("print_all\n");
    print_all(fila);

    printf("first: %d\n", first(fila));

    printf("dequeue: %d\n", dequeue(fila));
    printf("dequeue: %d\n", dequeue(fila));
    printf("dequeue: %d\n", dequeue(fila));
    printf("dequeue: %d\n", dequeue(fila));
    printf("dequeue: %d\n", dequeue(fila));
    // printf("dequeue: %d\n", dequeue(fila));

    if (empty(fila)) {
        printf("MAIN - Fila vazia.\n");
    }

    clear(fila);

    return 0;
}
