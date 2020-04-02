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
     cell->shot_counter = 0;
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

void shotCell(Cell *cell)
{
     if (cell->state == PIECE)
     {
          cell->state = PIECE_HITTED;
          decreaseActiveCell(cell->bellongsTo);
     }
     else if (cell->state == EMPTY)
     {
          cell->state = MISSED_SHOT;
     }
     cell->shot_counter++;
}

void decreaseActiveCell(Ship *ship)
{
     ship->ActiveCells--;
     if (!ship->ActiveCells)
     {
          //shipSank(ship); falta esat funçao
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
               if (player.myShips[i].index == 0)
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

               if (player.myShips[i].index == 2)
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

               if (player.myShips[i].index == 3)
               {
                    for (int row = player.myShips[i].gravity_point_row; row < (player.myShips[i].gravity_point_row + 5); row++)
                    {
                         Ship *barco = newShip(1);
                         int col = player.myShips[i].gravity_point_col;
                         if (row < 10 && col < 10)
                              updateCell(&matriz[row][col], 1, barco);
                    }
               }

               if (player.myShips[i].index == 1)
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
                              updateCell(&matriz[row-1][col + 1], 1, barco);
                    }
               }
          }
     }
     printMatriz(matriz);
}