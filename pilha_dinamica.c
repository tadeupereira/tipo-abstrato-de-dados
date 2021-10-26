#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *under;
} node;

typedef struct {
    node *top;
} stack;

stack *create(void) {
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

void clear(stack *s) {
    node *top = s->top;
    while (top != NULL) {
        node *temp = top->under;
        free(top);
        top = temp;
    }
    free(s);
}

int empty(stack *s) {
    return (s->top == NULL);
}

void push(stack *s, int v) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->value = v;
    new_node->under = s->top;
    s->top = new_node;
}

int pop(stack *s) {
    /* aborta programa */
    if (empty(s)) {
        printf("Pilha vazia.\n");
        exit(1);
    }
    int v = s->top->value;

    node *old_top = s->top;
    node *new_top = old_top->under;

    s->top = new_top;
    free(old_top);

    return v;
}

int top(stack *s) {
    /* aborta programa */
    if (empty(s)) {
        printf("Pilha vazia.\n");
        exit(1);
    }
    int v = s->top->value;

    return v;
}

void print_all(stack *s) {
    if (empty(s))
        printf("Pilha vazia.\n");
    else {
        node *n;
        for (n = s->top; n != NULL; n = n->under)
            printf("%d\n", n->value);
    }
}

int main() {

    stack *pilha;
    pilha = create();

    print_all(pilha);

    push(pilha, 10);
    push(pilha, 20);
    push(pilha, 30);

    printf("print_all\n");
    print_all(pilha);

    printf("top: %d\n", top(pilha));

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
