#include "../Obj/Board.h"
#include "../Obj/Ship.h"
#include <stdio.h>
#include <stdlib.h>
void toString(int size, PBoard board){
  for(int i = 0 ; i < size ; i++){
    for(int j = 0 ; j < size ; j++){
      printf("%d ",board.Mboard[i][j]);
    }
    puts("");
  }
}
PBoard makeBoard(int size){
  int *arr = malloc(sizeof(int*)*size);
  int *aux;
  for(int i = 0 ; i < size ; i++){
    aux= arr+i;
    aux= malloc(sizeof(int)*size);
   
  }
  int *a = arr[0];
  a[0] = 3;
  PBoard board = {17,size,&arr,&toString};  
  return board;
}
int main(void){
  int i = sizeof(int*);
  PBoard b = makeBoard(5);
  b.Mboard[0][0];
  printf("%d",i);
  return 0 ;
}

