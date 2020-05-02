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

Ship *newShip(int type, int n)
{
     Ship *ship = malloc(sizeof(Ship));
     ship->type = type;
     ship->ActiveCells = n; // missing a function to calculate the total
                            //amount of cells of a ship
     return ship;
}
void printMatriz(Cell matriz[40][40], int n)
{
     for (int i = 0; i < n; i++)
     {
          for (int j = 0; j < n; j++)
          {
               printf("%d ", matriz[i][j].state);
          }
          puts("");
     }
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
          Ship *barco = newShip(1,5);
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
          Ship *barco = newShip(1,5);
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
          Ship *barco = newShip(1,3);
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
          Ship *barco = newShip(1,7);
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
void print(Player *player, int size)
{
     printf(RED);
     printf("  -");
     for (int i = 0; i < size; i++)
     {
          printf("%d--", i);
     }
     puts("");
     for (int i = 0; i < size; i++)
     {
          printf(RED);
          printf("%d ", i);
          printf(RESET);
          for (int j = 0; j < size; j++)
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

void print_table(Player *player, int flag, int SIZE)
{
     printf("Os seus barcos\n");
     for (int i = 0; i < SIZE; i++)
     {
          for (int j = 0; j < SIZE; j++)
          {
               switch (player->matriz[i][j].state)
               {
               case 0:
                    printf(BLUE);
                    printf(" ~ ");
                    break;

               case 1:
                    printf(BOLDMAGENTA);
                    printf(" # ");
                    break;

               case 2:
                    printf(RED);
                    printf(" X ");
                    break;

               case 3:
                    printf(YELLOW);
                    printf(" O ");
                    break;
               }
          }
          printf(RESET);
          printf("\n");
     }

     printf("Os seus disparos\n");
     for (int i = 0; i < SIZE; i++)
     {
          printf("%d-- ", i);
     }
     puts("");

     for (int i = 0; i < SIZE; i++)
     {
          printf("%d  ", i);

          for (int j = 0; j < SIZE; j++)
          {
               switch (player->matriz[i][j].shotState)
               {
               case 0:
                    printf(BLUE);
                    printf(" ~ ");
                    break;

               case 1:
                    printf(BOLDMAGENTA);
                    printf(" # ");
                    break;

               case 2:
                    printf(RED);
                    printf(" X ");
                    break;

               case 3:
                    printf(YELLOW);
                    printf(" O ");
                    break;
               }
          }
          printf(RESET);
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
