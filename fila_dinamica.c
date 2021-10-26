#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct {
    node *first;
    node *last;
} queue;

queue *create(void) {
    queue *q = (queue *) malloc(sizeof(queue));
    q->first = q->last = NULL;
    return q;
}

void clear(queue *q) {
    node *first = q->first;
    while (first != NULL) {
        node *temp = first->next;
        free(first);
        first = temp;
    }
    free(q);
}

int empty(queue *q) {
    return (q->first == NULL);
}

void enqueue(queue *q, int v) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = v;
    new_node->next = NULL;    

    /* atualiza no final */
    if (q->last != NULL)
        q->last->next = new_node;

    q->last = new_node;
    /* atualiza lista vazia */
    if (q->first == NULL)
        q->first = q->last;
}

int dequeue(queue *q) {
    /* aborta programa */
    if (empty(q)) {
        printf("Fila vazia.\n");
        exit(1);
    }
    int v = q->first->value;

    node *old_first = q->first;
    node *new_first = old_first->next;

    q->first = new_first;
    free(old_first);

    return v;
}

int first(queue *q) {
    /* aborta programa */
    if (empty(q)) {
        printf("Fila vazia.\n");
        exit(1);
    }
    int v = q->first->value;

    return v;
}

void print_all(queue *q) {
    if (empty(q))
        printf("Fila vazia.\n");
    else {
        node *n;
        for (n = q->first; n != NULL; n = n->next)
            printf("%d\n", n->value);
    }
}

int main() {

    queue *fila;
    fila = create();

    print_all(fila);

    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);

    printf("print_all\n");
    print_all(fila);

    printf("first: %d\n", first(fila));

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
