#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main(){

     printf("\033[01;33m");  // bold yellow
     printf("     ____        _   _   _           _     _                  \n");
     printf("    | __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __             \n");
     printf("    |  _ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\            \n");
     printf("    | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |           \n");
     printf("    |____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/            \n");
     printf("                                            |_|               \n");
     printf("\033[0m");


     //  ------------- teste ----------------
      struct Ship* barco = newShip(1);
      struct Cell* matriz[10][10];
      int c = 0;
     for(int i = 0; i < 10; i++){
          for(int j = 0; j < 10; j++){

               matriz[i][j] = newCell();
          }
     }
     for(int i = 0; i < 10; i++){
          updateCell(matriz[i][0],1,barco);
     }

     for(int i = 0; i < 10; i++){
          for(int j = 0; j < 10; j++){
               printf("%d",matriz[i][j]->state);
          }
          printf("\n");
     }
     // ----------------- / / -------------------------

     return 0;
}
