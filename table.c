#include <stdio.h>
#include <stdlib.h>
#include "table.h"

enum State
{
     EMPTY,
     PIECE,
     PIECE_HITTED,
     MISSED_SHOT
};

void updateCell(Cell *cell, int state, Ship *bellongsTo)
{
     cell->state = state;
     cell->bellongsTo = bellongsTo;
}

Cell *newCell()
{
     Cell *cell = malloc(sizeof(cell));
     cell->state = 0;
     cell->shotState = 0;
     cell->bellongsTo = NULL;
     return cell;
}

int isFree(Cell *cell)
{ // when this function is used
     // only states 0 and 1 exists
     if (cell->state)
     {
          return 0;
     }
     return 1;
}
//
// void shotCell(Cell *cell)
// {
//      if (cell->state == PIECE)
//      {
//           cell->state = PIECE_HITTED;
//           decreaseActiveCell(cell->bellongsTo);
//      }
//      else if (cell->state == EMPTY)
//      {
//           cell->state = MISSED_SHOT;
//      }
//      cell->shot_counter++;
// }

void decreaseActiveCell(Ship *ship)
{
     ship->ActiveCells--;
     if (!ship->ActiveCells)
     {
     }
}

Ship *newShip(int type)
{
     Ship *ship = malloc(sizeof(Ship));
     ship->type = type;
     ship->ActiveCells = 10; // missing a function to calculate the total
                             //amount of cells of a ship
     return ship;
}
void printMatriz(Cell matriz[10][10])
{
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 10; j++)
          {
               printf("%d ", matriz[i][j].state);
          }
          puts("");
     }
}
void setUp(int size, Cell matriz[10][10], Player player)
{

     for (int i = 0; i < size; i++)
     {
          for (int j = 0; j < size; j++)
          {
               matriz[i][j] = *newCell();
          }
     }

     for (int i = 0; i < 5; i++)
     {
          for (int j = 0; j < player.myShips[i].amount; j++)
          {
               if (player.myShips[i].index == 1)
               {
                    // desenhando o T

                    if (player.myShips[i].rotate == 0)
                    {

                         int aux = 0;
                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 3); col++)
                         {
                              aux++;
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                              {
                                   updateCell(&matriz[row][col], 1, barco);
                              }
                              if (row > 0 && col > 0)
                              {

                                   Ship *barco = newShip(1);

                                   updateCell(&matriz[row][col - aux], 1, barco);
                              }
                         }

                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {

                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                              {
                                   Ship *barco = newShip(1);

                                   updateCell(&matriz[row][col], 1, barco);
                              }
                         }
                    }
                    if (player.myShips[i].rotate == 90)
                    {
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {

                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                              {
                                   Ship *barco = newShip(1);

                                   updateCell(&matriz[row][col], 1, barco);
                              }
                         }

                         for (int col = player.myShips[i].gravity_point_col - 3; col < (player.myShips[i].gravity_point_col); col++)
                         {

                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                              {
                                   updateCell(&matriz[row + 1][col], 1, barco);
                              }
                         }
                    }

                    if (player.myShips[i].rotate == 180)
                    {
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {

                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                              {
                                   Ship *barco = newShip(1);

                                   updateCell(&matriz[row][col], 1, barco);
                              }
                         }

                         int aux = 0;
                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 3); col++)
                         {
                              aux++;
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                              {
                                   updateCell(&matriz[row + 2][col], 1, barco);
                              }
                              if (row > 0 && col > 0)
                              {

                                   Ship *barco = newShip(1);

                                   updateCell(&matriz[row + 2][col - aux], 1, barco);
                              }
                         }
                    }
                    if (player.myShips[i].rotate == 270)
                    {
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {
                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col], 1, barco);
                         }

                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 3); col++)
                         {
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row + 1][col + 1], 1, barco);
                         }
                    }
               }

               if (player.myShips[i].index == 2)
               {
                    if (player.myShips[i].rotate == 0)
                    {
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {
                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col], 1, barco);
                         }

                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 2); col++)
                         {
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row + 2][col + 1], 1, barco);
                         }
                    }
                    if (player.myShips[i].rotate == 90)
                    {
                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 3); col++)
                         {
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col], 1, barco);
                         }

                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {
                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col], 1, barco);
                         }
                    }
                    if (player.myShips[i].rotate == 180)
                    {
                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 3); col++)
                         {
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row + 2][col], 1, barco);
                         }
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {
                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col + 2], 1, barco);
                         }
                    }
                    if (player.myShips[i].rotate == 270)
                    {
                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 3); col++)
                         {
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row + 2][col], 1, barco);
                         }
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {
                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col], 1, barco);
                         }
                    }
               }

               if (player.myShips[i].index == 3)
               {
                    if (player.myShips[i].rotate == 0 || player.myShips[i].rotate == 180)
                    {
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 5); row++)
                         {
                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col], 1, barco);
                         }
                    }
                    if (player.myShips[i].rotate == 270 || player.myShips[i].rotate == 90)
                    {
                         for (int col = player.myShips[i].gravity_point_col; col < (player.myShips[i].gravity_point_col + 5); col++)
                         {
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_col;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row][col], 1, barco);
                         }
                    }
               }

               if (player.myShips[i].index == 4)
               {
                    if (player.myShips[i].rotate == 0)
                    {
                         for (int col = player.myShips[i].gravity_point_col; col > (player.myShips[i].gravity_point_col - 3); col--)
                         {
                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row + 2][col + 1], 1, barco);
                         }
                         int col = player.myShips[i].gravity_point_col;

                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {
                              Ship *barco = newShip(1);

                              if (row < 10 && col < 10)
                              {
                                   updateCell(&matriz[row][col], 1, barco);
                                   col--;
                              }
                         }

                         for (int col = player.myShips[i].gravity_point_col; col > (player.myShips[i].gravity_point_col - 4); col--)
                         {

                              Ship *barco = newShip(1);
                              int row = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row - 1][col + 1], 1, barco);
                         }
                    }

                    if (player.myShips[i].rotate == 90)
                    {
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {

                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row - 1][col], 1, barco);
                         }
                         int aux = 0;
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {

                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_row;

                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row - 1][col + aux], 1, barco);
                              aux++;
                         }
                         for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 3); row++)
                         {

                              Ship *barco = newShip(1);
                              int col = player.myShips[i].gravity_point_row;
                              if (row < 10 && col < 10)
                                   updateCell(&matriz[row - 1][col + 3], 1, barco);
                         }
                    }
                    if (player.myShips[i].rotate == 180)
                    {
                    }
               }
          }
     }
     printMatriz(matriz);
}

void initializeMatriz(Player *player, int size)
{

     for (int i = 0; i < size; i++)
     {
          for (int j = 0; j < size; j++)
          {
               player->matriz[i][j] = *newCell();
          }
     }
}
void putSingleShip(Player *player, int index)
{
     if (index == 0)
     {
          Ship *barco = newShip(1);
          int row = player->myShips[index].gravity_point_row;
          int col = player->myShips[index].gravity_point_col;
          //desenhar o T
          switch (player->myShips[index].rotate)
          {
          case 0:
               //desenhando parte superior
               puts("debug");
               for (int i = player->myShips[index].gravity_point_col; i < player->myShips[index].gravity_point_col + 3; i++)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               //desenhando parte inferior
               updateCell(&player->matriz[row + 1][col + 1], 1, barco);
               updateCell(&player->matriz[row + 2][col + 1], 1, barco);

               break;

          case 90:
               col += 2;
               row = player->myShips[index].gravity_point_row - 1;
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               //desenhando parte inferior
               updateCell(&player->matriz[row + 1][col - 1], 1, barco);
               updateCell(&player->matriz[row + 1][col - 2], 1, barco);

               break;
          case 180:
               row += 1;
               for (int i = player->myShips[index].gravity_point_col; i < player->myShips[index].gravity_point_col + 3; i++)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               //desenhando parte inferior
               updateCell(&player->matriz[row - 1][col + 1], 1, barco);
               updateCell(&player->matriz[row - 2][col + 1], 1, barco);

               break;
          case 270:
               row -= 1;
               col -= 1;
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               //desenhando parte inferior
               updateCell(&player->matriz[row + 1][col + 1], 1, barco);
               updateCell(&player->matriz[row + 1][col + 2], 1, barco);
               break;
          }
     }
     if (index == 1)
     {
          //desenhando o l
          Ship *barco = newShip(1);
          int row = player->myShips[index].gravity_point_row;
          int col = player->myShips[index].gravity_point_col;
          int aux = 0;

          switch (player->myShips[index].rotate)
          {
          case 0:
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               updateCell(&player->matriz[row + 2][col + 1], 1, barco);
               updateCell(&player->matriz[row + 2][col + 2], 1, barco);

               break;
          case 90:
               aux = col + 3;
               for (int i = aux; i > col; i--)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               updateCell(&player->matriz[row + 1][col + 1], 1, barco);
               updateCell(&player->matriz[row + 2][col + 1], 1, barco);

               break;

          case 180:
               aux = row + 2;
               col += 2;
               for (int i = aux; i >= row; i--)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               updateCell(&player->matriz[row][col - 1], 1, barco);
               updateCell(&player->matriz[row][col - 2], 1, barco);

               break;
          case 270:
               row += 2;
               col -= 1;
               for (int i = col; i < col + 3; i++)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               updateCell(&player->matriz[row - 1][col + 2], 1, barco);
               updateCell(&player->matriz[row - 2][col + 2], 1, barco);

               break;
          default:
               break;
          }
     }
     if (index == 2)
     {
          //desenhando o I
          Ship *barco = newShip(1);
          int row = player->myShips[index].gravity_point_row;
          int col = player->myShips[index].gravity_point_col;
          int aux = 0;
          switch (player->myShips[index].rotate)
          {
          case 0:
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               break;
          case 90:
               row += 1;
               for (int i = col; i < col + 3; i++)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               break;
          case 180:
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               break;
          case 270:
               row += 1;
               for (int i = col; i < col + 3; i++)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               break;
          }
     }
     if (index == 3)
     {
          //desenhando o Z
          Ship *barco = newShip(1);
          int row = player->myShips[index].gravity_point_row;
          int col = player->myShips[index].gravity_point_col;
          int aux = 0;
          switch (player->myShips[index].rotate)
          {
          case 0:

               for (int i = col; i < col + 3; i++)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               updateCell(&player->matriz[row + 1][col + 1], 1, barco);
               updateCell(&player->matriz[row + 2][col], 1, barco);
               for (int i = col; i < col + 3; i++)
               {
                    updateCell(&player->matriz[row + 3][i], 1, barco);
               }
               break;
          case 90:
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               updateCell(&player->matriz[row + 1][col + 1], 1, barco);
               updateCell(&player->matriz[row][col + 2], 1, barco);
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col + 2], 1, barco);
               }
               break;
          case 180:
               for (int i = col; i < col + 3; i++)
               {
                    updateCell(&player->matriz[row][i], 1, barco);
               }
               updateCell(&player->matriz[row + 1][col + 1], 1, barco);
               updateCell(&player->matriz[row + 2][col], 1, barco);
               for (int i = col; i < col + 3; i++)
               {
                    updateCell(&player->matriz[row + 3][i], 1, barco);
               }
               break;
          case 270:
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col], 1, barco);
               }
               updateCell(&player->matriz[row + 1][col + 1], 1, barco);
               updateCell(&player->matriz[row][col + 2], 1, barco);
               for (int i = row; i < row + 3; i++)
               {
                    updateCell(&player->matriz[i][col + 2], 1, barco);
               }
               break;
          }
     }
}
void print(Player *player)
{
     printf(RED);
     printf("  -");
     for (int i = 0; i < 10; i++)
     {
          printf("%d--", i);
     }
     puts("");
     for (int i = 0; i < 10; i++)
     {
          printf(RED);
          printf("%d ", i);
          printf(RESET);
          for (int j = 0; j < 10; j++)
          {
               if (player->matriz[i][j].state == 1)
               {
                    printf(BLUE);
               }
               else
               {
                    printf(RESET);
               }
               printf("-%d-", player->matriz[i][j].state);
          }
          puts("");
     }
}
//--------------------------------------------------------------------

void updateCellShort(Cell *cell, int state)
{
     cell->state = state;
}
int shipSank(Ship *ship)
{
     if (ship->ActiveCells == 0)
     {
          return 1;
     }
     return 0;
}

void print_table(Player *player, int flag)
{
     int SIZE = 10; // temporario
     printf("Os seus barcos\n");
     for (int i = 0; i < SIZE; i++)
     {
          for (int j = 0; j < SIZE; j++)
          {
               switch (player->matriz[i][j].state)
               {
               case 0:
                    printf(" ~ ");
                    break;

               case 1:
                    printf(" # ");
                    break;

               case 2:
                    printf(" X ");
                    break;

               case 3:
                    printf(" O ");
                    break;
               }
          }
          printf("\n");
     }

     printf("Os seus disparos\n");
     for (int i = 0; i < SIZE; i++)
     {
          for (int j = 0; j < SIZE; j++)
          {
               switch (player->matriz[i][j].shotState)
               {
               case 0:
                    printf(" ~ ");
                    break;

               case 1:
                    printf(" # ");
                    break;

               case 2:
                    printf(" X ");
                    break;

               case 3:
                    printf(" O ");
                    break;
               }
          }
          printf("\n");
     }
     if (flag)
     {
          puts("Prima n para continuar");
          char next = ' ';
          while (next != 'n')
          {
               scanf("%c", &next);
          }
     }
     // puts("Prima n para continuar");
     // char next = ' ';
     // while(next != 'n'){
     //      scanf("%c",&next);
     // }
}

void changePlayer()
{
     puts("Proximo jogador prima n tecla para jogar");
     char next = ' ';
     while (next != 'n')
     {
          scanf("%c", &next);
     }
}

int ScanAndShot(Player *source_player, Player *target_player)
{
     int x, y;
     while (1)
     {
          printf("escolha o alvo dos seus disparos.\n");
          scanf("%d", &x);
          scanf("%d", &y); // cornfirmar se esta no range
          if (target_player->matriz[x][y].state == EMPTY)
          {
               updateCellShort(&target_player->matriz[x][y], MISSED_SHOT);
               source_player->matriz[x][y].shotState = MISSED_SHOT;
               system("clear");

               puts("Tiro falhado!");

               return 0;
          }
          else if (target_player->matriz[x][y].state == PIECE)
          {
               updateCellShort(&target_player->matriz[x][y], PIECE_HITTED);
               source_player->matriz[x][y].shotState = PIECE_HITTED;
               target_player->matriz[x][y].bellongsTo->ActiveCells--;
               system("clear");
               puts("Barco atingido!");
               if (shipSank(target_player->matriz[x][y].bellongsTo))
               {
                    target_player->activeShips--;
                    puts("Barco afundado!");
               }
               if (target_player->activeShips == 0)
               {
                    puts("Venceu o jogo!");
                    //flag para acabar o jogo
                    return 1;
               }

               return 0;
          }

          puts("Disparo repetido, tente outra vez!");
     }

     return 0;
}
