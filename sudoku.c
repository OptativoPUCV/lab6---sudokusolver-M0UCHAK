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

int is_valid(Node* n) {
    for (int row = 0; row < 9; row++) {
        int used_row[10] = {0};
        int used_col[10] = {0};

        for (int col = 0; col < 9; col++) {
            int num_row = n->sudo[row][col];
            int num_col = n->sudo[col][row];

            if (num_row != 0) {
                if (used_row[num_row] == 1) return 0;
                used_row[num_row] = 1;
            }

            if (num_col != 0) {
                if (used_col[num_col] == 1) return 0;
                used_col[num_col] = 1;
            }
        }
    }

    for (int k = 0; k < 9; k++) {
        int used[10] = {0};

        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);
            int j = 3 * (k % 3) + (p % 3);
            int num = n->sudo[i][j];

            if (num != 0) {
                if (used[num] == 1) return 0;
                used[num] = 1;
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

List* get_adj_nodes(Node* n){
  
  List *list = createList();

  for(int row = 0; row < 9; row++){
    for(int col = 0; col < 9; col++){
      
      if(n->sudo[row][col] == 0){
        for(int val = 1; val <= 9; val++){
          
          Node *adjNodes = copy(n);
          adjNodes->sudo[row][col] = val;
          if(is_valid(adjNodes)) pushBack(list, adjNodes); 
          
        }          
        return list;
      }
    }
  }
  return list;
}

int is_final(Node* n)
{
  for(int i = 0; i < 9; i++)
  {
    for(int k = 0; k < 9; k++)
    {
      if(n->sudo[i][k] == 0) return 0;
    }
  }
  return 1;
}

void freeStack(Stack* stack) {
    while (!is_empty(stack)) {
        void* data = pop(stack);
        free(data);
    }
    free(stack);
}

Node* DFS(Node* initial, int* cont){

  Stack* stack = createStack();
  push(stack, initial);

  while (!is_empty(stack)) {
        Node* current = (Node*)pop(stack);

        (*cont)++; 

        if (is_final(current)) {
            freeStack(stack);
            return current;
        }
  }
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