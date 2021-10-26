#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int value[MAX];
    int pointer;
} list;

list *create(void) {
    list *l = (list *) malloc(sizeof(list));
    l->pointer = 0;
    return l;
}

void clear(list *l) {
    free(l);
}

int empty(list *l) {
    return (l->pointer == 0);
}

int full(list *l) {
    return (l->pointer == MAX);
}

void insertFirst(list *l, int v) {
    /* aborta programa */
    if (full(l)) {
        printf("Capacidade da lista estourou.\n");
        exit(1);
    }

    l->pointer++;
    for (int i = l->pointer - 1; i > 0; i--)
        l->value[i] = l->value[i - 1];

    l->value[0] = v;
}


void insertLast(list *l, int v) {
    /* aborta programa */
    if (full(l)) {
        printf("Capacidade da lista estourou.\n");
        exit(1);
    }

    l->value[l->pointer] = v;
    l->pointer++;
}

void insert(list *l, int v, int position) {
    /* aborta programa */
    if (full(l)) {
        printf("Capacidade da lista estourou.\n");
        exit(1);
    }

    if (position < 1 || position > MAX) {
        printf("Posição indica não existe na lista.\n");
        exit(1);
    }

    l->pointer++;
    for (int i = l->pointer - 1; i > position - 1; i--)
        l->value[i] = l->value[i - 1];
    
    l->value[position - 1] = v;
}

int deleteFirst(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }

    int v = l->value[0];
    
    l->pointer--;
    for (int i = 0; i < l->pointer; i++)
        l->value[i] = l->value[i + 1];

    return v;
}

int deleteLast(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }

    l->pointer--;
    int v = l->value[l->pointer];

    return v;
}

int delete(list *l, int v) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }

    int position = -1;

    for (int i = 0; i < l->pointer; i++)
        if (l->value[i] == v) {
            position = i;
            break;
        }

    if (position != -1) {
      l->pointer--;
      for (int i = position; i < l->pointer; i++)
          l->value[i] = l->value[i + 1];
    }

    return (position != -1);
}

int searchFirst(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }

    int v = l->value[0];

    return v;
}

int searchLast(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }

    int v = l->value[l->pointer - 1];

    return v;
}

int search(list *l, int position) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }

    int v = l->value[position - 1];

    return v;
}

void print_all(list *l) {
    if (empty(l))
        printf("Lista vazia.\n");
    else {
        for (int i = 0; i < l->pointer; i++)
            printf("%d\n", l->value[i]);
    }
}

int main() {

    list *lista;
    lista = create();

    print_all(lista);

    insertLast(lista, 10);
    insertLast(lista, 20);
    insertLast(lista, 30);
    insertLast(lista, 40);
    insertLast(lista, 50);

    if (full(lista)) {
        printf("MAIN - Lista cheia.\n");
    }

    printf("deleteLast: %d\n", deleteLast(lista));
    printf("deleteLast: %d\n", deleteLast(lista));

    printf("print_all\n");
    print_all(lista);

    insertFirst(lista, 60);
    insert(lista, 70, 3);

    printf("print_all\n");
    print_all(lista);

    printf("searchFirst: %d\n", searchFirst(lista));    
    printf("searchLast: %d\n", searchLast(lista));
    printf("search: %d\n", search(lista, 3));

    for (int i = 10; i < 200; i += 100) {
        if ( delete(lista, i) ) {
            printf("MAIN - Item %d deleteado.\n", i);
        } else {
          printf("MAIN - Item %d não localizado para deletar.\n", i);
        }
    }

    printf("deleteFirst: %d\n", deleteFirst(lista));
    printf("deleteFirst: %d\n", deleteFirst(lista));
    printf("deleteLast: %d\n", deleteLast(lista));
    printf("deleteLast: %d\n", deleteLast(lista));
    // printf("deleteLast: %d\n", deleteLast(lista));

    if (empty(lista)) {
        printf("MAIN - Fila vazia.\n");
    }

    clear(lista);

    return 0;
}
