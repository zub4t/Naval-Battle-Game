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

void updateCell(Cell *cell, int state, Ship bellongsTo)
{
     cell->state = state;
     cell->bellongsTo = bellongsTo;
}

Cell *newCell()
{
     Cell *cell = malloc(sizeof(cell));
     cell->state = 0;
     cell->shotState = 0;
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

Ship newShip(int type, int n)
{
     Ship ship = {type,n};
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
     {      player->total_pieces+=5;
          Ship barco = newShip(1, 5);
          player->activeShips++;
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
     {      player->total_pieces+=5;
          //desenhando o l
          Ship barco = newShip(1, 5);
          player->activeShips++;

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
     {      player->total_pieces+=3;
          //desenhando o I
          Ship barco = newShip(1, 3);
          player->activeShips++;

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
     {      player->total_pieces+=8;
          //desenhando o Z
          Ship barco = newShip(1, 7);
          player->activeShips++;

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
     printf("   -");
     for (int i = 0; i < size; i++)
     {
          if (i >= 10)
               printf("%d-", i);
          else
               printf("%d--", i);
     }
     puts("\n");
     for (int i = 0; i < size; i++)
     {
          printf(RED);
          if (i < 10)
               printf("%d  ", i);
          else
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
int shipSank(Ship ship)
{
     if (ship.ActiveCells == 0)
     {
          return 1;
     }
     return 0;
}

void print_table(Player *player, int flag, int SIZE)
{
     printf(" Tem %d barcos que ainda não foram destruidos\n", player->activeShips);

     printf("Os seus barcos\n");
     for (int i = 0; i < SIZE; i++)
     {
          for (int j = 0; j < SIZE; j++)
          {
               switch (player->matriz[i][j].state)
               {
               case 0:
                    printf(BOLDBLUE);
                    printf(" ~ ");
                    break;

               case 1:
                    printf(BOLDMAGENTA);
                    printf(" # ");
                    break;

               case 2:
                    printf(BOLDRED);
                    printf(" X ");
                    break;

               case 3:
                    printf(BOLDYELLOW);
                    printf(" O ");
                    break;
               }
          }
          printf(RESET);
          printf("\n");
     }

     printf("Os seus disparos\n");
     printf(RED);
     printf("    ");
     for (int i = 0; i < SIZE; i++)
     {
          if (i >= 10)
               printf("%d ", i);
          else
               printf("%d  ", i);
     }
     puts("\n");

     for (int i = 0; i < SIZE; i++)
     {
          printf(RED);
          if (i < 10)
               printf("%d  ", i);
          else
               printf("%d ", i);
          printf(RESET);

          for (int j = 0; j < SIZE; j++)
          {
               switch (player->matriz[i][j].shotState)
               {
               case 0:
                    printf(BOLDBLUE);
                    printf(" ~ ");
                    break;

               case 1:
                    printf(BOLDMAGENTA);
                    printf(" # ");
                    break;

               case 2:
                    printf(BOLDRED);
                    printf(" X ");
                    break;

               case 3:
                    printf(BOLDYELLOW);
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
     int x=0, y=0;
     while (1)
     {
          printf("escolha o alvo dos seus disparos.\n");
          scanf("%d", &x);
          scanf("%d", &y); // cornfirmar se esta no range

          
          if (target_player->matriz[x][y].state == EMPTY)
          {
               puts("atualizando tiro");
               updateCellShort(&target_player->matriz[x][y], MISSED_SHOT);
               source_player->matriz[x][y].shotState = MISSED_SHOT;
               system("clear");

               puts("Tiro falhado!");

               return 0;
          }
          else if (target_player->matriz[x][y].state == PIECE)
          {
               puts("tiro confirmado");
               updateCellShort(&target_player->matriz[x][y], PIECE_HITTED);
               source_player->matriz[x][y].shotState = PIECE_HITTED;
               target_player->matriz[x][y].bellongsTo.ActiveCells--;
               system("clear");
               puts("Barco atingido!");
               target_player->total_pieces--;
               if (target_player->total_pieces== 0)
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
int randomN(int lower, int upper)
{

     return (rand() %
             (upper - lower + 1)) +
            lower;
}
void write_conf(char *name,Player *p){

     FILE *f = fopen(name, "w+");
     if (f == NULL)
     {
     printf("Error opening file!\n");
 
     }
     for(int i = 0; i<40;i++){
          for(int j = 0;j<40;j++){
               int aux = p->matriz[i][j].state;
               fprintf(f, "%d",aux);
          }
          fprintf(f, "-");
     }  
     fprintf(f, "F");
     for(int i = 0; i<40;i++){
          for(int j = 0;j<40;j++){
               int aux = p->matriz[i][j].shotState;
               fprintf(f, "%d",aux);
          }
            fprintf(f, "-");

     } 
     fclose(f);
}
void read_conf(char *name,Player *p){

     FILE *fp = fopen(name, "r");
     if (fp == NULL)
     {
          printf("Error opening file!\n");
     }
     int c;
     int n = 0, i= 0, j=0;
  
     do {
          c = fgetc(fp);
          if( c=='F' || i==40) {
               break ;
          }
          if( c=='-') {
               j=0;
               i++;

          }
          if( c=='-') {
          //  puts("");
          }else{
               //printf("%d",c);
               p->matriz[i][j].state=(c-48);
               j++;

          }
       
       
       
     
     } while(1);
  //   puts("shot State");
     //shot State
     i=0;
     j=0;
     do {
          c = fgetc(fp);
          if(feof(fp)|| i==40) {
               break ;
          }
          if( c=='-') {
               j=0;
               i++;

          } 
          if( c=='-') {
         //   puts("");
          }else{
            //   printf("%d",c);
               p->matriz[i][j].shotState=(c-48);
               j++;

          }
     } while(1);


     fclose(fp);
}