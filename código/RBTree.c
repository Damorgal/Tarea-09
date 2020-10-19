#include <stdio.h>
#include <stdlib.h>

typedef struct RBT{
    int key;
    int value;
    int color;
    struct RBT *left;
    struct RBT *right;
    struct RBT *parent;
} RBT;

// API
void put(RBT *s, int key, int val);
int get(RBT *s, int key);
int contains(RBT *s, int key);
void delete(RBT *s, int key);
int isEmpty(RBT *s);
int size(RBT *s);
void inorder_traversal(RBT *s);

// Variable global para obtener el número de elementos
int count = 0;

// -------------------------------------------------

// Insertar nuevo nodo
// Falta colorear y reacomodar

void put(RBT *s, int key, int val){

    // Si no se tiene valor de llave, crear nuevo nodo
    if(s->key == 0){
        s->key = key;
        s->value = val;
        s->left = (RBT *)malloc(sizeof(RBT));
        s->right = (RBT *)malloc(sizeof(RBT));
        s->left->parent = s;
        s->right->parent = s;

        return;
    }

    // La nueva llave es más grande que la llave del nodo
    if(key > s->key){
        put(s->right, key, val);
    }

    // La nueva llave es más pequeña que la llave del nodo
    if(key < s->key){
        put(s->left, key, val);
    }

}

// Devuelve el valor asociado a la llave
int get(RBT *s, int key){

    // Si se llega a un nodo terminal
    if(s->key == 0){
        return -1;
    }

    // En caso de encontrar la llave
    else if(key == s->key){
        return s->value;
    }

    // Lo que se busca es más grande que la llave del nodo
    else if(key > s->key){
        return get(s->right, key);
    }

    // Lo que se busca es más pequeño que la llave del nodo
    else if(key < s->key){
        return get(s->left, key);
    }
}


// ¿Existe algún nodo con la llave?
// 1 éxito, 0 fracaso
int contains(RBT *s, int key){

    // Si se llega a un nodo terminal
    if(s->key == 0){
        return -1;
    }

    // Se encuentra la llave
    else if(key == s->key){
        return 1;
    }

    // Lo que se busca es más grande que la llave del nodo
    else if(key > s->key){
        return get(s->right, key);
    }

    // Lo que se busca es más pequeño que la llave del nodo
    else if(key < s->key){
        return get(s->left, key);
    }

}


// 0 si está vacío, 1 si tiene algún elemento
int isEmpty(RBT *s){
    return (s->key != 0);
}


// Número de elementos en el árbol, sin contar nodos terminales
int size(RBT *s){

    count = 0;
    
    // Si no se cuenta con ningún elemento
    if(s->key == 0){
        return count;
    }

    // Recorrer la lista para obtener número de elementos
    inorder_traversal(s);

    return count;
}

// Se recorre el ABB en orden
void inorder_traversal(RBT *s){

    if(s->left->key != 0){
        inorder_traversal(s->left);
    }

    count++;

    if(s->right->key != 0){
        inorder_traversal(s->right);
    }

    return;
}


// Pruebas parciales, tentativamente se creará "specs.c"
int main(){

    RBT *my_tree = (RBT*)malloc(sizeof(RBT));
    printf("%d ", size(my_tree));

}
