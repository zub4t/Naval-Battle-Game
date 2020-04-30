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
     Player p1 = {0, 5,malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100)};
     Player p2 = {0, 5,malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100)};
     puts("primeiro jogador escolhendo navios");
     initializeMatriz(&p1, 10);
     chooseShips(&p1);
     puts("segundo  jogador escolhendo navios");
     initializeMatriz(&p2, 10);
     chooseShips(&p2);
     startGame(&p1,&p2);


     return 0;
}

void startGame(Player *p1, Player *p2){
     while(1){
          system("clear");
          changePlayer();
          system("clear");


          //enter para aparecer tabelas player 1
          // print board barcos player 1 e tiros player 1
          print_table(p1,0);
          // p1 scan target
          if(ScanAndShot(p1,p2)){ //target
               return;
          }

          //clear

          //print feedback
          // print tabelas atualizadas
          print_table(p1,1);
          //enter para desaparecer tabelas player 1
          system("clear");

          //------------------ proximo jogador -------------------------------

          changePlayer();
          system("clear");

          //enter para aparecer tabelas player 2
          //print board barcos player 2 e tiros player 2
          print_table(p2,0);

          // p2 scan target
          if(ScanAndShot(p2,p1)){ //target
               return;
          }
          system("clear");

          //clear
          //printfeedback
          //print tabelas atualizadas
          print_table(p2,1);

          //enter para desaparecer tabelas player 2


     }

}

void chooseShips(Player *player)
{
     int amount = 0, size = 0;
     size = 4;
     player->myShips = malloc(sizeof(Node) * size);

     for (int i = 0; i < size; i++)
     {

          player->myShips[i].gravity_point_row = 0;
          player->myShips[i].gravity_point_col = 0;
          player->myShips[i].rotate = 0;
          int row = 0;
          int col = 0;
          int rotate = 0;

          int flag = 0;
          do
          {
               printf("Defina a linha e coluna para colocar o barco de nº %d ex: 2 5 \n ", i);
               scanf("%d", &row);
               scanf("%d", &col);
               flag = 0;
               puts("Defina a rotação do barco");

               scanf("%d", &rotate);
               switch (i)
               {
               case 0:
                    switch (rotate)
                    {
                    case 0:
                         if (col + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (row + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 90:
                         if (row - 1 < 0)

                              if (col + 2 > 10)
                              {
                                   puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                   flag = 1;
                              }
                         if (row + 1 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col - 2 < 0)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 180:
                         if (row - 1 < 0)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col - 1 < 0)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 270:
                         if (col - 1 < 0)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (row - 1 < 0)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (row + 1 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    }

                    break;

               case 1:
                    switch (rotate)
                    {
                    case 0:
                         if (row + 3 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col + 3 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;

                    case 90:
                         if (row + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col + 3 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 180:
                         if (row + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 270:
                         if (col + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (row + 2 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col - 1 < 0)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    }
                    break;

               case 2:
                    switch (rotate)
                    {
                    case 0:
                         if (row + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 90:
                         if (col + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 180:
                         if (row + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 270:
                         if (col + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    }
                    break;
               case 3:
                    switch (rotate)
                    {
                    case 0:
                         if (col + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (row + 3 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 90:
                         if (row + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col + 3 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 180:
                         if (col + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (row + 3 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    case 270:
                         if (row + 3 > 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         if (col + 3 >= 10)
                         {
                              puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                              flag = 1;
                         }
                         break;
                    }
               }
          } while (flag);

          player->myShips[i].gravity_point_row = row;
          player->myShips[i].gravity_point_col = col;
          player->myShips[i].rotate = rotate;
          player->myShips[i].value.type = i;
          player->myShips[i].amount = amount;
          player->myShips[i].index = i;
          putSingleShip(player, i);
          print(player);
     }
}
