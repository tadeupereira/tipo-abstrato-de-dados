#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef enum {
    FREE, BUSY
} STATUS;

typedef struct {
    int key;
    int value;
} bucket;

typedef struct {
    bucket *buckets[SIZE];
    STATUS status[SIZE];
    int used;
} hash;

// Função hashing - Tentativa linear
int hashing(int key) {
    return key % SIZE;
}

int get_index(hash *h, int k) {
    int i = 0;
    int index = hashing(k);
    while ( i < SIZE 
      && h->status[index] == BUSY
      && h->buckets[index]->key != k) {
        i++;
        index = hashing(k + i);
    }

    return index;
}

hash *create(void) {
    hash *h = (hash *) malloc(sizeof(hash));
    for (int i = 0; i < SIZE; i++) {
        h->buckets[i] = NULL;
        h->status[i] = FREE;
    }
    h->used = 0;
    return h;
}

void clear(hash *h) {
    free(h);
}

int empty(hash *h) {
    return (h->used == 0);
}

int full(hash *h) {
    return (h->used == SIZE);
}

void put(hash *h, int k, int v) {
    /* aborta programa */
    if (full(h)) {
        printf("Capacidade da tabela estourou.\n");
        exit(1);
    }

    int index = get_index(h, k);

    if (h->status[index] == BUSY) {
        h->buckets[index]->value = v;
    } else {
        bucket *put_bucket = (bucket *) malloc(sizeof(bucket));
        put_bucket->key = k;
        put_bucket->value = v;

        h->buckets[index] = put_bucket;
        h->status[index] = BUSY;
        h->used++;
    }
}

bucket *get(hash *h, int k) {
    /* aborta programa */
    if (empty(h)) {
        printf("Tabela vazia.\n");
        exit(1);
    }

    int index = get_index(h, k);
    bucket *get_bucket = NULL;

    if ( h->status[index] == BUSY
      && h->buckets[index]->key == k) {
        get_bucket = h->buckets[index];
    }

    return get_bucket;
}

bucket *delete(hash *h, int k) {
    /* aborta programa */
    if (empty(h)) {
        printf("Tabela vazia.\n");
        exit(1);
    }

    int index = get_index(h, k);
    bucket *delete_bucket = NULL;

    if ( h->status[index] == BUSY
      && h->buckets[index]->key == k) {
        delete_bucket = h->buckets[index];
        h->buckets[index] = NULL;
        h->status[index] = FREE;
        
    }

    return delete_bucket;
}

void print_all(hash *h) {
    if (empty(h))
        printf("Tabela vazia.\n");
    else {
        for (int i = 0; i < SIZE; i++) {
            bucket *print_bucket = h->buckets[i];
            if (h->status[i] != FREE && print_bucket != NULL)
                printf("Chave: %d\tValor: %d\n", 
                    print_bucket->key, print_bucket->value);
        }
    }
}

int main() {
    hash *tabela;
    tabela = create();
    bucket *bucket_temp = NULL;

    put(tabela, 11, 1111);
    put(tabela, 12, 1212);
    put(tabela, 13, 1313);
    put(tabela, 14, 1414);

    printf("\nMostrando todas as chaves\n");
    print_all(tabela);

    put(tabela, 14, 4444);
    put(tabela, 18, 1818);
    
    if (full(tabela)) {
        printf("\nMAIN - Tabela cheia.\n");
    }

    printf("\nMostrando todas as chaves\n");
    print_all(tabela);
    
    printf("\nBuscando chave\n");
    for (int i = 17; i < 19; i++) {
        bucket_temp = get(tabela, i);
        if (bucket_temp == NULL)
            printf("Chave %d não existe!\n", i);
        else printf("Chave: %d\tValor: %d\n", 
          bucket_temp->key, bucket_temp->value);
    }

    printf("\nExcluindo chave\n");
    for (int i = 17; i < 19; i++) {
        bucket_temp = delete(tabela, i);
        if (bucket_temp == NULL)
            printf("Chave %d não existe!\n", i);
        else printf("Chave: %d\tValor: %d\n", 
          bucket_temp->key, bucket_temp->value);
    }

    printf("\nMostrando todas as chaves\n");
    print_all(tabela);

    free(bucket_temp);
    clear(tabela);

    return 0;
}
