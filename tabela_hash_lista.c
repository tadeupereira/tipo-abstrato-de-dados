#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct bucket {
    int key;
    int value;
    struct bucket *next;
} bucket;

typedef struct {
    bucket *buckets[SIZE];
} hash;

// Função hashing
int hashing(int key) {
    return key % SIZE;
}

bucket *create_bucket(int k, int v, bucket *n) {
    bucket *new_bucket = (bucket *) malloc(sizeof(bucket));
    new_bucket->key = k;
    new_bucket->value = v;
    new_bucket->next = n;
    return new_bucket;
}

hash *create(void) {
    hash *h = (hash *) malloc(sizeof(hash));
    for (int i = 0; i < SIZE; i++)
        h->buckets[i] = NULL;
    return h;
}

void clear(hash *h) {
    free(h);
}

void put(hash *h, int k, int v) {
    int index = hashing(k);
    bucket *put_bucket = h->buckets[index];

    if (put_bucket == NULL) {
        put_bucket = create_bucket(k, v, NULL);
        h->buckets[index] = put_bucket;
    } else {
        while (put_bucket != NULL && put_bucket->key != k)
            put_bucket = put_bucket->next;

        if (put_bucket == NULL) {
            put_bucket = h->buckets[index];
            h->buckets[index] = create_bucket(k, v, put_bucket);
        } else {
            put_bucket->value = v;
        }
    }
}

bucket *get(hash *h, int k) {
    int index = hashing(k);
    bucket *get_bucket = h->buckets[index];

    while (get_bucket != NULL && get_bucket->key != k)
        get_bucket = get_bucket->next;

    return get_bucket;
}

bucket *delete(hash *h, int k) {
    int index = hashing(k);
    bucket *delete_bucket = h->buckets[index];

    if (delete_bucket != NULL) {
        
        if (delete_bucket->key == k) {
            h->buckets[index] = delete_bucket->next;
            delete_bucket->next = NULL;
        } else {
            bucket *prior_bucket = delete_bucket;
            while (prior_bucket->next != NULL && prior_bucket->next-> key != k)
                prior_bucket = prior_bucket->next;

            if (prior_bucket->next == NULL || prior_bucket->next->key != k)
                delete_bucket = NULL;
            else {
                delete_bucket = prior_bucket->next;
                prior_bucket->next = delete_bucket->next;
                delete_bucket->next = NULL;
            }
        }

    }

    return delete_bucket;
}

void print_all(hash *h) {
    for (int i = 0; i < SIZE; i++) {
        bucket *print_bucket = h->buckets[i];
        while (print_bucket != NULL) {
            printf("Índice: %d\tChave: %d\tValor: %d\n", 
                i, print_bucket->key, print_bucket->value);
            print_bucket = print_bucket->next;
        }
    }
}

int main(void) {

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
    
    printf("\nMostrando todas as chaves\n");
    print_all(tabela);
    
    printf("\nBuscando chave\n");
    for (int i = 17; i < 20; i++) {
        bucket_temp = get(tabela, i);
        if (bucket_temp == NULL)
            printf("Chave %d não existe!\n", i);
        else printf("Chave: %d\tValor: %d\n", 
          bucket_temp->key, bucket_temp->value);
    }

    printf("\nExcluindo chave\n");
    for (int i = 17; i < 20; i++) {
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
