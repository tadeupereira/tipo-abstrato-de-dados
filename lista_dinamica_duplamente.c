#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *prior, *next;
} node;

typedef struct {
    int count;
    node *first;
    node *last;
} list;

list *create(void) {
    list *l = (list *) malloc(sizeof(list));
    l->first = l->last = NULL;
    l->count = 0;
    return l;
}

void clear(list *l) {
    node *first = l->first;
    while (first != NULL) {
        node *temp = first->next;
        free(first);
        first = temp;
    }
    free(l);
}

int empty(list *l) {
    return (l->first == NULL);
}

void insertFirst(list *l, int v) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = v;
    new_node->next = l->first;

    l->first->prior = new_node;

    l->first = new_node;
    /* atualiza lista vazia */
    if (l->last == NULL)
        l->last = l->first;

    l->count++;
}

void insertLast(list *l, int v) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = v;
    new_node->next = NULL;

    /* atualiza no final */
    if (l->last != NULL)
        l->last->next = new_node;

    new_node->prior = l->last;    

    l->last = new_node;
    /* atualiza lista vazia */
    if (l->first == NULL)
        l->first = l->last;

    l->count++;
}

void insert(list *l, int v, int position) {
    /* aborta programa */
    if (empty(l) || position == 1) {
        insertFirst(l, v);
        return;
    } else if (position > l->count) {
        insertLast(l, v);
        return;
    } else if (position < 1) {
        printf("Posição indica não existe na lista.\n");
        exit(1);
    }
    
    node *position_node = l->first;
    for (int i = 1; i < position; i++)
        position_node = position_node->next;

    node *insert_node = (node *) malloc(sizeof(node));
    insert_node->value = v;
    insert_node->prior = position_node->prior;
    insert_node->next = position_node;

    position_node->prior->next = insert_node;
    position_node->prior = insert_node;

    l->count++;    
}

int deleteFirst(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }
    
    int v = l->first->value;

    if (l->first == l->last) {
        free(l->first);
        l->first = l->last = NULL;
        l->count = 0;
    } else {
        node *old_first = l->first;
        node *new_first = old_first->next;

        new_first->prior = NULL;
        l->first->prior = new_first;

        l->first = new_first;
        free(old_first);
        l->count--;
    }

    return v;
}

int deleteLast(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }
    
    int v = l->last->value;

    if (l->first == l->last) {
        free(l->first);
        l->first = l->last = NULL;
        l->count = 0;
    } else {
        node *old_last = l->last;
        node *new_last = l->first;

        while (new_last->next != old_last) {
          new_last = new_last->next;
        }

        new_last->next = NULL;

        l->last = new_last;
        free(old_last);
        l->count--;
    }

    return v;
}

int delete(list *l, int v) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }

    if (l->first->value == v){
        return deleteFirst(l);
    } else if (l->last->value == v){
        return deleteLast(l);
    }

    node *delete_node = l->first->next;
    while(delete_node != NULL && delete_node->value != v)
        delete_node = delete_node->next;

    int result = (delete_node != NULL && delete_node->value == v);

    if (result) {
        delete_node->prior->next = delete_node->next;
        delete_node->next->prior = delete_node->prior;

        free(delete_node);
        l->count--;
    }

    return result;
}

int searchFirst(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }
    int v = l->first->value;    

    return v;
}

int searchLast(list *l) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    }
    int v = l->last->value;

    return v;
}

int search(list *l, int position) {
    /* aborta programa */
    if (empty(l)) {
        printf("Lista vazia.\n");
        exit(1);
    } 

    if (position == 1) {
        return searchFirst(l);
    } else if (position >= l->count) {
        return searchLast(l);
    }

    node *current = l->first;
    
    for (int i = 2; i <= position; i++)
        current = current->next;

    int v = current->value;        

    return v;
}

void print_all_asc(list *l) {
    if (empty(l))
        printf("Lista vazia.\n");
    else {
        node *n;
        for (n = l->first; n != NULL; n = n->next)
            printf("%d\n", n->value);
    }
}

void print_all_desc(list *l) {
    if (empty(l))
        printf("Lista vazia.\n");
    else {
        node *n;
        for (n = l->last; n != NULL; n = n->prior)
            // printf("%d\n", n->value);
            printf("%d\t%d\t%d\n", n->value,
                n->prior == NULL ? -1 :n->prior->value,
                n->next == NULL ? -1 : n->next->value);
    }
}

int main() {

    list *lista;
    lista = create();

    print_all_asc(lista);

    insertLast(lista, 10);
    insertLast(lista, 20);
    insertLast(lista, 30);
    insertLast(lista, 40);
    insertLast(lista, 50);

    printf("deleteLast: %d\n", deleteLast(lista));
    printf("deleteLast: %d\n", deleteLast(lista));

    printf("print_all_asc\n");
    print_all_asc(lista);
    printf("print_all_desc\n");
    print_all_desc(lista);

    insertFirst(lista, 60);
    insert(lista, 70, 3);

    printf("print_all_asc\n");
    print_all_asc(lista);
    printf("print_all_desc\n");
    print_all_desc(lista);

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

    printf("print_all_asc\n");
    print_all_asc(lista);
    printf("print_all_desc\n");
    print_all_desc(lista);

    printf("deleteLast: %d\n", deleteLast(lista));
    // printf("deleteLast: %d\n", deleteLast(lista));

    if (empty(lista)) {
        printf("MAIN - Fila vazia.\n");
    }

    clear(lista);

    return 0;
}
