#include <stdio.h>
#include <stdlib.h>
#include "./RBTree.c"

// Imprimir colores
void inorder_print_colors(RBT *s){
    
    if(s->left != NULL){
        inorder_print_colors(s->left);
    }

    printf("%d \t", s->color);

    if(s->right != NULL){
        inorder_print_colors(s->right);
    }

    return;
}

int main(){

    int nodes = 0;
    int key = 0, value = 0;
    printf("\nInserte el número de nodos que quisiera agregar: ");
    scanf("%d", &nodes);

    printf("\nInserción de nodos (key/value)\n\n");
    
    printf("Nodo 1: ");
    scanf("%d %d", &key, &value);
    RBT *my_tree = (RBT*)malloc(sizeof(RBT));

    my_tree->key = key;
    my_tree->value = value;
    my_tree->parent = NULL;
    my_tree->right = NULL;
    my_tree->left = NULL;
    my_tree->color = BLACK;

    for(int i = 1; i < nodes; i++){
        printf("Nodo %d: ", i+1);
        scanf("%d %d", &key, &value);
        my_tree = put(my_tree, key, value);
    }

    printf("\nImpresión en orden (BST)\n");
    inorder_print(my_tree);
    printf("\n\n Colores asignados (RBT)\n");
    inorder_print_colors(my_tree);
    printf("\n");

    free(my_tree);

    return 0;
}
