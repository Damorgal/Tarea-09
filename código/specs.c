#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "./RBTree.c"

#define TOTALTESTS 4
int passed = 0;

int test_insert_elements(void){ 

  printf("\nAgregando elementos: \n"); 

    RBT *my_tree = (RBT*)malloc(sizeof(RBT));

    //Primeros elementos
    my_tree->key = 3;
    my_tree->value = 5;
    my_tree->parent = NULL;
    my_tree->right = NULL;
    my_tree->left = NULL;
    my_tree->color = BLACK;
    
    //Siguientes
    my_tree = put(my_tree,-3,5);
    my_tree = put(my_tree,0,5);
    my_tree = put(my_tree,10,5);
    my_tree = put(my_tree,12,5);
    my_tree = put(my_tree,-1,5);
    my_tree = put(my_tree,-4,5);
    my_tree = put(my_tree,33,5);
    my_tree = put(my_tree,16,5);
    my_tree = put(my_tree,-6,5);
    my_tree = put(my_tree,-14,5);

    if(size(my_tree) != 11){
        printf("No se insertaron correctamente los nodos\n");
        return 0;
    }

    printf("El número de elementos agregados era el esperado\n");
    free_RBT(my_tree);

    passed +=1;
    return 1;
} 

int test_remove_elements(void){ 

    printf("\nPrueba de eliminación de elementos\n"); 
    printf("Elementos iniciales: 5\n");
    RBT *my_tree = (RBT*)malloc(sizeof(RBT));

    //Primeros elementos
    my_tree->key = 3;
    my_tree->value = 5;
    my_tree->parent = NULL;
    my_tree->right = NULL;
    my_tree->left = NULL;
    my_tree->color = BLACK;
    
    //Siguientes
    my_tree = put(my_tree,-3,5);
    my_tree = put(my_tree,0,5);
    my_tree = put(my_tree,10,5);
    my_tree = put(my_tree,12,5);
    delete(my_tree, 12);

    printf("Un elemento fue eliminado\n");
    if(size(my_tree) != 4){
        printf("El tamaño del arbol no es el esperado\n");
        return 0;
    }

    printf("Eliminacion correcta\n");
    free_RBT(my_tree);

    passed +=1;
    return 1;
} 

int test_free_RBT(){

    printf("\nPrueba de liberacion de memoria\n"); 
    RBT *my_tree = (RBT*)malloc(sizeof(RBT));

    //Primeros elementos
    my_tree->key = 3;
    my_tree->value = 5;
    my_tree->parent = NULL;
    my_tree->right = NULL;
    my_tree->left = NULL;
    my_tree->color = BLACK;
    
    //Siguientes
    my_tree = put(my_tree,-3,5);
    my_tree = put(my_tree,0,5);
    my_tree = put(my_tree,10,5);
    my_tree = put(my_tree,12,5);

    free_RBT(my_tree);

    printf("El valor de la llave no debería ser el establecido\n");
    if(my_tree->key == 3){
        printf("No se ha liberado correctamente la memoria\n");
        return 0;
    }

    printf("Prueba satisfactoria\n");
    passed +=1;
    return 1;
}

int test_inorder_print(){

    printf("\nLa lista debe visualizarse de menor a mayor:\n");
        RBT *my_tree = (RBT*)malloc(sizeof(RBT));

    //Primeros elementos
    my_tree->key = 3;
    my_tree->value = 5;
    my_tree->parent = NULL;
    my_tree->right = NULL;
    my_tree->left = NULL;
    my_tree->color = BLACK;
    
    //Siguientes
    my_tree = put(my_tree,-3,5);
    my_tree = put(my_tree,0,5);
    my_tree = put(my_tree,10,5);
    my_tree = put(my_tree,12,5);

    inorder_print(my_tree);
    printf("\n");

    free_RBT(my_tree);

    passed += 1;
    return 1;
}

int main(int argc, char * argv[]){

  int all_tests_ok = 1;
    
    all_tests_ok *= test_insert_elements();
    all_tests_ok *= test_remove_elements();
    all_tests_ok *= test_free_RBT();
    all_tests_ok *= test_inorder_print();

    printf("\nTotal de pruebas realizadas: %d\n", TOTALTESTS);
    printf("Total de pruebas exitosas: %d\n", passed) ;
    printf("Total de pruebas fallidas: %d\n", TOTALTESTS - passed);

    assert(all_tests_ok); 
    printf("\n");

    return 0;
} 
