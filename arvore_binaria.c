#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} node;

typedef struct {
    int count;
    node *root;
} tree;

tree *create(void) {
    tree *t = (tree *) malloc(sizeof(tree));
    t->root = NULL;
    t->count = 0;
    return t;
}

int empty(tree *t) {
    return (t->root == NULL);
}

void insert(tree *t, int v) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->left = new_node->right = NULL;
    new_node->value = v;

    node *node_father = NULL;
    node *node_insert = t->root;
    
    while (node_insert != NULL) {
      node_father = node_insert;
      if (new_node->value < node_insert->value)
          node_insert = node_insert->left;
      else
          node_insert = node_insert->right;
    }

    if (node_father == NULL)
        t->root = new_node;
    else if (new_node->value < node_father->value)
        node_father->left = new_node;
    else
        node_father->right = new_node;
    t->count++;
}

void insert_hard(tree *t) {
    int count = 0;

    // Nível 4
    node *new_05 = (node *) malloc(sizeof(node));
    new_05->left = new_05->right = NULL;
    new_05->value = 5;
    count++;

    node *new_15 = (node *) malloc(sizeof(node));
    new_15->left = new_15->right = NULL;
    new_15->value = 15;
    count++;

    // Nível 3
    node *new_10 = (node *) malloc(sizeof(node));
    new_10->left = new_05;
    new_10->right = new_15;
    new_10->value = 10;
    count++;

    node *new_40 = (node *) malloc(sizeof(node));
    new_40->left = new_40->right = NULL;
    new_40->value = 40;
    count++;

    node *new_60 = (node *) malloc(sizeof(node));
    new_60->left = new_60->right = NULL;
    new_60->value = 60;
    count++;

    // Nível 2
    node *new_20 = (node *) malloc(sizeof(node));
    new_20->left = new_10;
    new_20->right = NULL;
    new_20->value = 20;
    count++;

    node *new_50 = (node *) malloc(sizeof(node));
    new_50->left = new_40;
    new_50->right = new_60;
    new_50->value = 50;
    count++;

    // Nível 1
    node *new_30 = (node *) malloc(sizeof(node));
    new_30->left = new_20;
    new_30->right = new_50;
    new_30->value = 30;
    count++;

    t->root = new_30;
    t->count = count;
}

int delete(tree *t, int v) {
    /* aborta programa */
    if (empty(t)) {
        printf("Árvore vazia.\n");
        exit(1);
    }

    node *node_delete = t->root;
    node *node_father = NULL;
    node *node_son = NULL;
    node *node_temp = NULL;

    while (node_delete != NULL && node_delete->value != v) {
      node_father = node_delete;
      if (v < node_delete->value)
          node_delete = node_delete->left;
      else
          node_delete = node_delete->right;
    }
    
    if (node_delete == NULL) {
        return 0;
    }
    
    if (node_father == NULL) {
        if (node_delete->right == NULL) {
            t->root = node_delete->left;
        } else if (node_delete->left == NULL) {
            t->root = node_delete->right;
        } else {

            for (
              node_temp = node_delete, node_son = node_delete->left; 
              node_son->right != NULL;
              node_temp = node_son, node_son = node_son->right);
            
            if (node_son != node_delete->left) {
              node_temp->right = node_son->left;
              node_son->left = t->root->left;              
            }
            node_son->right = t->root->right;
            t->root = node_son;
        }        
    } else if (node_delete->right == NULL) {
        if (node_father->left == node_delete)
            node_father->left = node_delete->left;
        else
            node_father->right = node_delete->left;
    } else if (node_delete->left == NULL) {
        if (node_father->left == node_delete)
            node_father->left = node_delete->right;
        else
            node_father->right = node_delete->right;
    } else {
        for (
          node_temp = node_delete, node_son = node_delete->left; 
          node_son->right != NULL;
          node_temp = node_son, node_son = node_son->right);
				
        if (node_son != node_delete->left) {
          node_temp->right = node_son->left;
          node_son->left = node_delete->left;
        }
        node_son->right = node_delete->right;
				
        if (node_father->left == node_delete)
          node_father->left = node_son;
        else
          node_father->right = node_son;    
    }

    free(node_delete);

    t->count--;

    return 1;
}

int exist(tree *t, int v) {
    /* aborta programa */
    if (empty(t)) {
        printf("Árvore vazia.\n");
        exit(1);
    }

    node *node_exist = t->root;

    while (node_exist != NULL && node_exist->value != v) {
      if (v < node_exist->value)
          node_exist = node_exist->left;
      else
          node_exist = node_exist->right;
    }

    return (node_exist != NULL);
}

node *get(tree *t, int v) {
    /* aborta programa */
    if (empty(t)) {
        printf("Árvore vazia.\n");
        exit(1);
    }

    node *node_get = t->root;

    while (node_get != NULL && node_get->value != v) {
      if (v < node_get->value)
          node_get = node_get->left;
      else
          node_get = node_get->right;
    }

    return node_get;
}

int height_node(node *n){
    if (n == NULL){
        return 0;
    }

    int l_height = height_node(n->left); 
    int r_height = height_node(n->right);

    if (l_height > r_height)
        return ++l_height;
    else
        return ++r_height;
}

int height_tree(tree *t) {
    if (empty(t)) {
        printf("Árvore vazia.\n");
        exit(1);
    }

    return height_node(t->root);
}

int max_node_tree(int height_tree) {
    // float qt_nos_arvore = pow(2, i) - 1;
    return (int) pow(2, height_tree) - 1;
}

int max_node_leaf(int height_tree) {
    // float qt_nos_folha = pow(2, i - 1);
    return (int) pow(2, height_tree - 1);
}

int max_node_height(int height_tree, int height_node) {
    // float qt_nos_nivel = pow(2, i - j);
    return (int) pow(2, height_tree - height_node);
}

int space_node_begin(int height_node) {
    // float qt_espaco_inicio = pow(2, j) - 2;
    // return (int) pow(2, height_node) - 2;
    return (int) pow(2, height_node) + height_node * 2 - 4;
}

int space_node_between(int height_node) {
    // float qt_espaco_nos = pow(2, j + 1) - 2;
    // return (int) pow(2, height_node + 1) - 2;
    return (int) pow(2, height_node + 1);
}

char *int2str(int value) {
    const int TAM = 5;
    char *buffer = malloc(TAM * sizeof(char));
    char *str_result = malloc(TAM * sizeof(char));
    int str_size;

    snprintf(buffer, TAM,"%d",value);

    str_size = strlen(buffer);
    if (str_size % 2 != 0) {
        char *str_size_2 = malloc(TAM * sizeof(char));
        strcpy(str_size_2, "0");
        strcpy(str_size_2 + 1, buffer);
        strcpy(buffer, str_size_2);
        str_size++;
        free(str_size_2);
    }

    str_size = (TAM - str_size) / 2;
    for (int i = 0; i < str_size; i++)
        strcpy(str_result + i, " ");

    strcpy(str_result + str_size, buffer);

    str_size = strlen(str_result);
    for (int i = str_size; i < TAM - 1; i++)
        strcpy(str_result + i, " ");

    free(buffer);

    return str_result;
}

void print_nodes(node *n, int height, int show_height) {
    if (n == NULL) {
        return;
    }

    if (show_height)
        printf("Altura: %d\t\tValor: %d\n", height, n->value);
    else
        printf("%d\n", n->value);
    
    height++;
    print_nodes(n->left, height, show_height);
    print_nodes(n->right, height, show_height);
}

void print_tree(tree *t, int show_height) {
    if (empty(t))
        printf("Árvore vazia.\n");
    else {
        print_nodes(t->root, 1, show_height);
    }
}

void print_graph_space(int space) {
    for (int i = space; i > 0; i--){
        printf(" ");
    }
}

void print_graph_edge(int height) {
    if (height < 2)
      return;
    
    int space = space_node_begin(height - 1) + 3;
    for (int i = space; i > 0; i--){
        printf(" ");
    }

    int edge = space_node_between(height - 1) / 2;
    for (int j = 0; j < 2; j++) {
      for (int i = edge; i > 0; i--){
          printf("-");
      }
      printf("  ");
    }
}

void print_graph_height(node *node, int height_new, int height, int space){
    if (node == NULL)
      return;

    if(height_new == height) {
        print_graph_space(space);
        printf("%s", int2str(node->value));
    } else {
        if (node->left == NULL)
            print_graph_space(space);
        print_graph_height(node->left, height_new - 1, height, space);
        
        space = space_node_between(height);
        
        if (node->right == NULL)
            print_graph_space(space);
        print_graph_height(node->right, height_new - 1, height, space);
    }
}

void print_graph(tree* t){
    if (empty(t)) {
        printf("Árvore vazia.\n");
        exit(1);
    }

    int height = height_tree(t);
    for (int i = height; i > 0; i--){
        int space = space_node_begin(i);
        print_graph_height(t->root, height, i, space);
        printf("\n");
        print_graph_edge(i);
        printf("\n");
    }
}

int main(void) {
    tree *arvore;
    arvore = create();
    
    // insert_hard(arvore);
    insert(arvore, 30);
    insert(arvore, 20);
    insert(arvore, 50);
    insert(arvore, 10);
    insert(arvore, 15);
    insert(arvore, 40);
    insert(arvore, 60);
    insert(arvore, 5);

    // insert(arvore, 1);    
    // insert(arvore, 0);
    // insert(arvore, 2);
    // insert(arvore, 6);
    // insert(arvore, 35);
    // insert(arvore, 45);
    // insert(arvore, 13);
    // insert(arvore, 17);

    printf("\nQuant. : %d\n", arvore->count);

    printf("\n\nexist\n\n");
    for (int i = 0; i <= 60; i = i + 5) {
        if (exist(arvore, i)) {
          printf("Localizado:\t\t%d\n", i);
        } else {
          printf("Não localizado:\t%d\n", i);
        }
    }

    
    int height = height_tree(arvore);
    printf("\nAltura : %d\n", height_tree(arvore));

    printf("\n\nprint_tree\n\n");
    print_tree(arvore, 1);
    print_tree(arvore, 0);
    
    printf("\n\nprint_nodes\n\n");
    node *node_get = get(arvore, 20);
    print_nodes(node_get, height, 0);

    // print_graph(arvore);

    printf("\n\ndelete\n\n");
    for (int i = 0; i <= 60; i = i + 5) {
        if (delete(arvore, i)) {
            printf("Excluido:\t\t%d\t\tQuant. : %d\n", i, arvore->count);
        } else {
            printf("Não excluido:\t%d\t\tQuant. : %d\n", i, arvore->count);
        }
    }

    if (empty(arvore)) {
        printf("\n\nMAIN - Árvore vazia.\n\n");
    }

}
