#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef struct RBT{
    int key;
    int value;
    int color; //0 es negro y 1 es rojo
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
void rightRot(RBT *s);
void leftRot(RBT *s);
RBT *grand(RBT *s);
RBT *uncle(RBT *s);
RBT *insert(RBT *s, int key, int val);
void check(RBT *s);
void change(RBT *s);
void checkRot(RBT *s);

// Variable global para obtener el número de elementos
int count = 0;

// -------------------------------------------------

//Función para encontrar el abuelo rápido
RBT *grand(RBT *s)  {
    if ((s != NULL) && (s->parent != NULL))
        return s->parent->parent;
    else
        return NULL;
}

RBT *uncle(RBT *s)  {
    RBT *aux = grand(s);
    if (s->parent == aux->left)
        return aux->right;
    else
        return aux->left;
}

// Rotación a la derecha para corrección de propiedades
void rightRot(RBT *s)   {
    //Auxiliar del que vamos a rotar
    RBT *aux = s->left;
    
    if(aux == NULL) {printf("Error, Rotas a la derecha una hoja\n"); exit(1);}
    
    //Si somos hijos derechos/izquierdos actualizamos padre del nodo
    if(s->parent!=NULL && s->parent->right==s)
        s->parent->right = aux;
    else if(s->parent!=NULL && s->parent->left==s)
        s->parent->left = aux;
    aux->parent = s->parent;
    
    //Actualizamos el hijo izquierdo 
    s->left = aux->right;
    s->left->parent = s;
    
    //Actualizamos el hijo derecho del nodo 
    aux->right = s;
    s->parent = aux;
}

// Rotación a la derecha para corrección de propiedades
void leftRot(RBT *s)    {
    //Auxiliar del que vamos a rotar
    RBT *aux = s->right;
    
    if(aux == NULL) {printf("Error, Rotas a la izquierda una hoja\n"); exit(1);}
    
    //Si somos hijos derechos actualizamos padre del nodo
    if(s->parent!=NULL && s->parent->right==s)
        s->parent->right = aux;
    else if(s->parent!=NULL && s->parent->left==s)
        s->parent->left = aux;
    aux->parent = s->parent;
    
    //Actualizamos el hijo derecho 
    s->right = aux->left;
    s->right->parent = s;
    
    //Actualizamos el hijo izquierdo del nodo 
    aux->left = s;
    s->parent = aux;
}

//Función para insertar nodo como un BBT
RBT *insert(RBT *s, int key, int val)   {
    // Si no se tiene valor de llave, crear nuevo nodo
    if(s == NULL){
        s = (RBT *)malloc(sizeof(RBT));
        s->key = key;
        s->value = val;
        s->left = NULL;//(RBT *)malloc(sizeof(RBT));
        s->right = NULL;//(RBT *)malloc(sizeof(RBT));
        s->parent = NULL;
        //s->left->parent = s;
        //s->right->parent = s;
        return s;
    }
    // La nueva llave es más grande que la llave del nodo
    if(key > s->key)    {
        if(s->right != NULL)
            insert(s->right, key, val);
        else    {
            s->right = (RBT*)malloc(sizeof(RBT));
            s->right->key = key;
            s->right->value = val;
            s->right->left = NULL;//(RBT *)malloc(sizeof(RBT));
            s->right->right = NULL;//(RBT *)malloc(sizeof(RBT));
            s->right->parent = s;
            return s->right;
        }
    }
    // La nueva llave es más pequeña que la llave del nodo
    else    {
        if(s->left != NULL)
            insert(s->left, key, val);
        else {
            s->left = (RBT*)malloc(sizeof(RBT));
            s->left->key = key;
            s->left->value = val;
            s->left->left = NULL;//(RBT *)malloc(sizeof(RBT));
            s->left->right = NULL;//(RBT *)malloc(sizeof(RBT));
            s->left->parent = s;
            return s->left;
        }
    }
}

void check(RBT *s) {
    //Si somos el primer nodo
    if(s->parent == NULL)
        s->color = BLACK;
    //Si no cambiamos colores
    else {
        //No hay nada que hacer
        if (s->parent->color == BLACK)
            return;
        else    
            //Es rojo y debemos cambiar
            change(s);
    }
}

void change(RBT *s) {
    RBT *tio = uncle(s), *abu = grand(s);
    //Al entrar aquí el papá es rojo, si el tio también es
    //Los cambiamos a negro y cambiamos a rojo al abuelo
    if ((tio != NULL) && (tio->color == RED)) {
        s->parent->color = BLACK;
        tio->color = BLACK;
        abu->color = RED;
        check(abu);
    } 
    else {
        //Tio negro, checamos a los hijos para ver posible rotacion
        checkRot(s);
    }
}

void checkRot(RBT *s)    {
    RBT *abu = grand(s);
    //Si el papá es hijo izquierdo del abuelo y el nodo es hijo derecho
    if ((s == s->parent->right) && (s->parent == abu->left)) {
        leftRot(s->parent);
        s = s->left;
    } 
    //Si el papá es hijo derecho del abuelo y el nodo es hijo izquierdo
    else if((s == s->parent->left) && (s->parent == abu->right)) {
        rightRot(s->parent);
        s = s->right;
    }
    //Sino Hacemos una rotación sobre el abuelo
    abu = grand(s);
    s->parent->color = BLACK;
    abu->color = RED;
    //Si el papá es hijo izquierdo al igual que el nodo
    if ((s == s->parent->left) && (s->parent == abu->left))
        rightRot(abu);
    //Sino, el papá es hijo derecho al igual que el nodo
    else 
        leftRot(abu);
}

// Insertar nuevo nodo
// Falta colorear y reacomodar

void put(RBT *s, int key, int val) {
    //Insertamos como un BBT normal
    RBT *node = insert(s, key, val);
    
    // Verificamos la coloración
    check(node);
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

