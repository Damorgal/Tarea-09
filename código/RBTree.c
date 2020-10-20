#include <stdio.h>
#include <stdlib.h>
#include "./tools.c"

// API
RBT *put(RBT *s, int key, int val);
int get(RBT *s, int key);
int contains(RBT *s, int key);
void delete(RBT *s, int key);
int isEmpty(RBT *s);
int size(RBT *s);
void inorder_traversal(RBT *s);
void free_RBT(RBT *s);

// Variable global para obtener el número de elementos
int count = 0;

// -------------------------------------------------


// Insertar nuevo nodo
RBT *put(RBT *s, int key, int val) {
    //Insertamos como un BBT normal
    RBT *node = insert(s, key, val);
    
    // Verificamos la coloración
    check(node);
    
    //Actualizamos el nodo raiz
    while(s->parent != NULL)
        s = s->parent;
    return s;
}


// Devuelve el valor asociado a la llave
int get(RBT *s, int key){
    // Si se llega a un nodo terminal
    if(s == NULL){
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
    else {
        return get(s->left, key);
    }
}


// Devuelve el apuntador al nodo asociado a la llave
RBT *get_ptr(RBT *s, int key)   {
    // Si se llega a un nodo terminal
    if(s == NULL){
        return NULL;
    }
    
    // En caso de encontrar la llave
    else if(key == s->key){
        return s;
    }

    // Lo que se busca es más grande que la llave del nodo
    else if(key > s->key){
        return get_ptr(s->right, key);
    }

    // Lo que se busca es más pequeño que la llave del nodo
    else {
        return get_ptr(s->left, key);
    }
}


// ¿Existe algún nodo con la llave?
// 1 éxito, 0 fracaso
int contains(RBT *s, int key){
    // Si se llega a un nodo terminal
    if(s == NULL){
        return 0;
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
    else {
        return get(s->left, key);
    }

}

// 0 si está vacío, 1 si tiene algún elemento
int isEmpty(RBT *s) {
    return (s != NULL);
}


// Número de elementos en el árbol, sin contar nodos terminales
int size(RBT *s){
    
    count = 0;
    
    // Si no se cuenta con ningún elemento
    if(s == NULL){
        return count;
    }

    // Recorrer la lista para obtener número de elementos
    inorder_traversal(s);

    return count;
}


// Se recorre el ABB en orden
void inorder_traversal(RBT *s){
    count++;
    
    if(s->left != NULL){
        inorder_traversal(s->left);
    }
    if(s->right != NULL){
        inorder_traversal(s->right);
    }
    return;
}

// Eliminación de un nodo dada una llave
void delete(RBT *s, int key)    {
    //Buscamos primero el nodo
    RBT *node = get_ptr(s, key);
    //Si no lo encontramos
    if(node == NULL) {printf("Error, tratas de eliminar una llave inexistente\n"); return;}
    
    //Borramos como BST normal
    RBT *aux;
    //El más grande de los menores
    if(node->left != NULL)  {
        aux = node->left;
        while(aux->right != NULL)
            aux = aux->right;
        //Copiamos info
        node->key = aux->key;
        node->value = aux->value;
    }
    //El más pequeño de los mayores
    else if(node->right != NULL)  {
        aux = node->right;
        while(aux->left != NULL)
            aux = aux->left;
        //Copiamos info
        node->key = aux->key;
        node->value = aux->value;
    }
    //Sino no tiene hijos, actualizamos padre y borramos
    else  {
        //Si somos hijos derechos
        if(node->parent != NULL && node->parent->right == node)
            node->parent->right = NULL;
        //Sino somos izquierdos
        else if(node->parent != NULL)
            node->parent->left = NULL;
        free(node);
        return;
    }
    //Vemos si tiene hijos
    if(aux->left == NULL && aux->right == NULL) {
        //Si somos hijos derechos
        if(aux->parent != NULL && aux->parent->right == aux)
            aux->parent->right = NULL;
        //Sino somos izquierdos
        else if(aux->parent != NULL)
            aux->parent->left = NULL;
        free(aux);
        return;
    }
    //Sino, tiene al menos un hijo.
    checkDelete(aux);
}

void inorder_print(RBT *s){
    
    if(s->left != NULL){
        inorder_print(s->left);
    }

    printf("%d \t", s->key);

    if(s->right != NULL){
        inorder_print(s->right);
    }

    return;
}

// Se recorre todo el árbol para liberar memoria
void free_RBT(RBT *s){

    if(s == NULL){
        return;
    }

    free_RBT(s->left);
    free_RBT(s->right);

    free(s);
}
