#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main()
{

     printf("\033[01;33m"); // bold yellow
     printf("     ____        _   _   _           _     _                  \n");
     printf("    | __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __             \n");
     printf("    |  _ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\            \n");
     printf("    | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |           \n");
     printf("    |____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/            \n");
     printf("                                            |_|               \n");
     printf("\033[0m");

     //  ------------- teste ----------------
     Ship *barco = newShip(1);
     Player p1;
     Player p2;
     puts("primeiro jogador escolhendo navios");
     chooseShips(p1);
     puts("segundo  jogador escolhendo navios");
     chooseShips(p2);
     setUp(10, p1.matriz);
     setUp(10, p2.matriz);

     for (int i = 0; i < 10; i++)
     {
          updateCell(&p1.matriz[i][0], 1, barco);
     }

     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 10; j++)
          {
               printf("%d", p1.matriz[i][j].state);
          }
          printf("\n");
     }
     // ----------------- / / -------------------------

     return 0;
}

void chooseShips(Player player)
{
     int amount = 0, size = 0;
     size = 5;
     player.myShips = malloc(sizeof(Node) * size);

     for (int i = 1; i <= size; i++)
     {
          printf("Escolha a quantidade de barcos do tipo  %d \n", i);
          scanf("%d", &amount);
          player.myShips[i].value.type = i;
          player.myShips[i].amount = amount;
          player.myShips[i].index = i;
     }
}
