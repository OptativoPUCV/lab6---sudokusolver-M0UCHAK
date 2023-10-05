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

typedef struct ListNode {
    Node* data;
    struct ListNode* next;
} ListNode;

typedef struct List{
    ListNode* head;
} List;


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

int is_valid(Node* n){

  for(int row = 0; row < 9;row++){
    int used[10] = {0};
    
    for(int col = 0; col < 9; col++){
      int num = n -> sudo[row][col];
      
      if(num == 0) continue;
      if(used[num] == 1) return 0;
      used[num] = 1;
    }
  }
  
  for(int col = 0; col < 9; col++){
    int used[10] = {0};
    
    for(int row = 0; row < 9; row++){
      int num = n -> sudo[row][col];
      
      if(num == 0) continue;
      if(used[num] == 1) return 0;
      used[num] = 1;
    }
  }

  for (int startRow = 0; startRow < 9; startRow += 3) {
    for (int startCol = 0; startCol < 9; startCol += 3) {
      int used[10] = {0};
      
      for (int row = startRow; row < startRow + 3; row++) {
        for (int col = startCol; col < startCol + 3; col++) {
          int num = n->sudo[row][col];
          if (num == 0) continue; 
          if (used[num] == 1) return 0;
          used[num] = 1;
        }
      }
    }
  }
  return 1;
}

void appendToList(List* list, Node* data) {
  
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) list->head = newNode;
    else {
        ListNode* current = list->head;
        while (current->next != NULL) current = current->next;
        current->next = newNode;
    }
}

void freeList(List* list) {
  
  ListNode* current = list->head;
  
  while (current != NULL) {
    ListNode* next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
  free(list);
}

List* get_adj_nodes(Node* n) {
    List* list = createList();

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (n->sudo[row][col] == 0) {
                for (int val = 1; val <= 9; val++) {
                    Node* newNode = copy(n);
                    newNode->sudo[row][col] = val;

                    if (is_valid(newNode)) {
                        appendToList(list, newNode);
                    } else {
                        free(newNode);
                    }
                }
            }
        }
    }

    return list;
}



/*
List* get_adj_nodes(Node* n) {
  
  List* list = createList();

  int row, col;
  for (row = 0; row < 9; row++) {
    for (col = 0; col < 9; col++) {
      if (n->sudo[row][col] == 0) {
        for (int val = 1; val <= 9; val++) {
          Node* newNode = copy(n);
          newNode->sudo[row][col] = val;
          
          if (is_valid(newNode)) appendToList(list, newNode);
          else free(newNode); 
        }
        break;
      }
    }
    if (col < 9) break;
  }
  return list;
}*/

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