#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int cumpleFila(int sudo[9][9]) {
   int numActual;
   int fila,col;

   //recorrer cada fila
   for (fila = 0 ; fila < 9 ; fila++) {
      //           {1,2,3,4,5,6,7,8,9};
      int pos[9] = {0,0,0,0,0,0,0,0,0};
      
      //Recorrer cada columna
      for (col = 0 ; col < 9 ; col++) {

         //obtener numero de esa casilla y si esta vacia saltamos a lasiguiente
         numActual = sudo[fila][col];
         if (numActual == 0) continue;

         //aumentar y verificar el vector de apariciones
         if (pos[numActual - 1] == 0)
            pos[numActual - 1] = 1;
         else
            return 0;
      }
   }
   return 1;
}

int cumpleColumna(int sudo[9][9]) {
   int numActual;
   int fila,col;

   //Recorrer cada columna
   for (col = 0 ; col < 9 ; col++) {
      //           {1,2,3,4,5,6,7,8,9};
      int pos[9] = {0,0,0,0,0,0,0,0,0};
      
      //recorrer cada fila
      for (fila = 0 ; fila < 9 ; fila++) {
         numActual = sudo[fila][col];

         //obtener numero de esa casilla y si esta vacia saltamos a lasiguiente
         if (numActual == 0) continue;

         //aumentar y verificar el vector de apariciones
         if (pos[numActual - 1] == 0)
            pos[numActual - 1] = 1;
         else
            return 0;
      }
   }
   return 1;
}

int cumpleSubMatriz(int sudo[9][9]) {
   int numActual;
   
   //recorrer las 9 submatrices (0 hasta 8)
   for (int numSub = 0 ; numSub < 9 ; numSub++) {
      int pos[9] = {0,0,0,0,0,0,0,0,0};
      
      //recorrer los 9 numeros de la submatriz
      for(int p = 0 ; p < 9 ; p++){
         
         //calculo indices
         int i = 3 * (numSub/3) + (p/3) ;
         int j = 3 * (numSub%3) + (p%3) ;
         numActual = sudo[i][j];

         //obtener numero de esa casilla y si esta vacia saltamos a lasiguiente
         if (numActual == 0) continue;

         //aumentar y verificar el vector de apariciones
         if (pos[numActual - 1] == 0)
            pos[numActual - 1] = 1;
         else
            return 0;
      }
   }
   return 1;
}


int is_valid(Node* n) {
   return (cumpleFila(n->sudo) && cumpleColumna(n->sudo) && cumpleSubMatriz(n->sudo));
}


void insertarNumeros(Node *nodo, int fila, int columna, List *listaAdj) {
   //iteramos sobre los 9 numeros
   for (int num = 1 ; num < 10 ; num++) {
      //copiamos nodo en nuevo y reservamos memoria
      Node *nuevoNodo = copy(nodo);
      //inserto numero en la posicion
      nuevoNodo->sudo[fila][columna] = num;
      //inserto nodo a la lista
      pushBack(listaAdj, nuevoNodo);
   }
}


void insertarNumerosVerificados(Node *nodo, int fila, int columna, List *listaAdj) {
   //iteramos sobre los 9 numeros
   for (int num = 1 ; num < 10 ; num++) {
      //copiamos nodo en nuevo y reservamos memoria
      Node *nuevoNodo = copy(nodo);
      //inserto numero en la posicion
      nuevoNodo->sudo[fila][columna] = num;

      //verificamos que la posicion sea valida
      if (is_valid(nuevoNodo))
         pushBack(listaAdj, nuevoNodo);
      else
         free(nuevoNodo);
   }
}

List* get_adj_nodes(Node* n){
   List* list=createList();
   //buscamos posiciones vacias
   int i,k;
   for (i = 0; i < 9 ; i++) {
      for (k = 0; k < 9 ; k++) {
         if (n->sudo[i][k] == 0) {
            //agregamos 9 numeros en esa posicion a la lista
            insertarNumerosVerificados(n, i, k, list);
         }
      }
   }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/