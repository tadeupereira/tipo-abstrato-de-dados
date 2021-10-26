#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int value[MAX];
    int node;
} stack;

stack *create(void) {
    stack *s = (stack *) malloc(sizeof(stack));
    s->node = 0;
    return s;
}

void clear(stack *s) {
    free(s);
}

int empty(stack *s) {
    return (s->node == 0);
}

int full(stack *s) {
    return (s->node == MAX);
}

void push(stack *s, int v) {
    /* aborta programa */
    /* capacidade esgotada */
    if (full(s)) {
        printf("Capacidade da pilha estourou.\n");
        exit(1);
    }

    s->value[s->node] = v;
    s->node++;
}

int pop(stack *s) {
    /* aborta programa */
    if (empty(s)) {
        printf("Pilha vazia.\n");
        exit(1);
    }

    s->node--;
    int v = s->value[s->node];

    return v;
}

int top(stack *s) {
    /* aborta programa */
    if (empty(s)) {
        printf("Pilha vazia.\n");
        exit(1);
    }

    int v = s->value[s->node - 1];

    return v;
}

void print_all(stack *s) {
    if (empty(s))
        printf("Pilha vazia.\n");
    else {
        int i;
        for (i = s->node - 1; i >= 0; i--)
            printf("%d\n", s->value[i]);
    }
}

int main() {

    stack *pilha;
    pilha = create();

    print_all(pilha);

    push(pilha, 10);
    push(pilha, 20);
    push(pilha, 30);
    push(pilha, 40);
    push(pilha, 50);
    // push(pilha, 60);

    if (full(pilha)) {
        printf("MAIN - Pilha cheia.\n");
    }

    printf("pop: %d\n", pop(pilha));
    printf("pop: %d\n", pop(pilha));

    push(pilha, 60);
    push(pilha, 70);

    printf("print_all\n");
    print_all(pilha);

    printf("first: %d\n", top(pilha));

    printf("pop: %d\n", pop(pilha));
    printf("pop: %d\n", pop(pilha));
    printf("pop: %d\n", pop(pilha));
    printf("pop: %d\n", pop(pilha));
    printf("pop: %d\n", pop(pilha));
    // printf("pop: %d\n", pop(pilha));

    if (empty(pilha)) {
        printf("MAIN - Pilha vazia.\n");
    }

    clear(pilha);

    return 0;
}
