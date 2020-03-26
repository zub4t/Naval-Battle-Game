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
void setUp(int size, Cell matriz[10][10])
{

     for (int i = 0; i < size; i++)
     {
          for (int j = 0; j < size; j++)
          {
               matriz[i][j] = *newCell();
          }
     }
}