#include <stdio.h>
#include <stdlib.h>
#include "table.h"
#include <stdbool.h>


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
               source_player->matriz[x][y].shotState=MISSED_SHOT;

               puts("Tiro falhado!");

               return 0;
          }
          else if (target_player->matriz[x][y].state == PIECE)
          {
               puts("tiro confirmado");
               updateCellShort(&target_player->matriz[x][y], PIECE_HITTED);
               source_player->matriz[x][y].shotState = PIECE_HITTED;
               target_player->matriz[x][y].bellongsTo.ActiveCells--;
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
     fprintf(f, "%d",p->total_pieces);

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

               p->matriz[i][j].state=(c-48);
               j++;

          }




     } while(1);
     char str[3];
     str[0] = fgetc(fp);
     str[1]= fgetc(fp);
     str[2]=  '\0';
     int total = atoi(str);
     p->total_pieces= total;

     fclose(fp);
}


Point make_Point(int x, int y){
    Point p = {x,y};
    return p;
}

Point add_Point(Point p, Point q){
    Point Point = {p.x+q.x,p.y+q.y};
    return Point;
}


bool isEqual(Point p, Point q){
    return (p.x == q.x) && (p.y == q.y);
}

bool inSquare(Point p, Point corner, int side){
    return ((corner.x  <= p.x) && (p.x < corner.x+side)) &&
            ((corner.y <= p.y) && (p.y < corner.y+side));

}

void insertNodeP(QD_NODE* qd,QD_NODE* actual,Point p, int l){
     puts("inserir nos");
        Point point  = add_Point(p,p);
     insertNode(qd,actual,point,l*2);

}



void slpit(QD_NODE *qd,QD_NODE *actual,Point p, int l){
   //printf("split\n");
    QD_NODE *node = (QD_NODE*) malloc(l*l*sizeof(QD_NODE));
    node->type = QDLEAF;
    node->leaf.value = actual->leaf.value;
    node->leaf.p = actual->leaf.p;
    node->leaf.ocupied = true;
    actual->type = QDNODE;





    for(int i = 0; i < 4; i++){
        actual->quadrants[i] = (QD_NODE *) malloc(l*l*sizeof(QD_NODE));
        actual->quadrants[i]->type = QDLEAF;
        actual->quadrants[i]->leaf.ocupied = false;


    }
     actual->type = QDNODE;
     actual->leaf.ocupied = false;

 if(node->leaf.p.x < p.x + (l/2) && node->leaf.p.y >= p.y + (l/2)){
          printf("%d\n",l);
               actual->quadrants[topLeft] = node;



    }

    //quadrante NE
    else if(node->leaf.p.x >= p.x + (l/2) && node->leaf.p.y >= p.y + (l/2)){
                 actual->quadrants[topRight] = node;



    }

    //quadrante SO
    else if(node->leaf.p.x < p.x + (l/2) && node->leaf.p.y < p.y + (l/2)){
                 actual->quadrants[botLeft] = node;


    }

    //quadrante Sw
    else if(node->leaf.p.x >= p.x + (l/2) && node->leaf.p.y < p.y + (l/2)){
          actual->quadrants[botRight] = node;


    }




}
void insertNode(QD_NODE* qd,QD_NODE* actual,Point p, int l){



    if(qd == NULL){
      return;
    }

    if (!inSquare(qd->leaf.p, p, l)){
      return;
    }

    if(actual->type == QDLEAF && actual->leaf.ocupied){

        actual->leaf.ocupied = false;
        actual->type = QDNODE;
        slpit(qd,actual,p,l);
        insertNode(qd,actual,p,l);
        return;

    }

     if((!actual->leaf.ocupied) && actual->type == QDLEAF){
         actual->type = QDNODE;
         actual->leaf.ocupied = true;
         actual->leaf.value = qd->leaf.value;
         actual->leaf.p = qd->leaf.p;


        return;
    }
     //quadrante NO
    if(qd->leaf.p.x < p.x + (l/2) && qd->leaf.p.y >= p.y + (l/2)){

      if(qd->quadrants[topLeft] == NULL){
          qd->quadrants[topLeft] =(QD_NODE *) malloc(l*l*sizeof(QD_NODE));
          qd->quadrants[topLeft]->type = QDLEAF;
          qd->quadrants[topLeft]->leaf.ocupied = false;


      }
      Point point = {p.x,p.y+(l/2)};
     insertNode(qd,qd->quadrants[topLeft], point, l/2);


    }

    //quadrante NE
    else if(qd->leaf.p.x >= p.x + (l/2) && qd->leaf.p.y >= p.y + (l/2)){
          if(qd->quadrants[topRight] == NULL){
               qd->quadrants[topRight] = (QD_NODE *) malloc(l*l*sizeof(QD_NODE));
               qd->quadrants[topRight]->type = QDLEAF;
               qd->quadrants[topRight]->leaf.ocupied = false;


      }

          Point point = {p.x+(l/2),p.y+(l/2)};
          insertNode(qd,qd->quadrants[topRight], point, l/2);

    }

    //quadrante SO
    else if(qd->leaf.p.x < p.x + (l/2) && qd->leaf.p.y < p.y + (l/2)){
                 printf("botLeft\n");
          if(qd->quadrants[botLeft] == NULL){
               qd->quadrants[botLeft] = (QD_NODE *) malloc(l*l*sizeof(QD_NODE));
               qd->quadrants[botLeft]->type = QDLEAF;
               qd->quadrants[botLeft]->leaf.ocupied = false;


         }
         Point point = {p.x,p.y};
      insertNode(qd,qd->quadrants[botLeft], point, l/2);
    }

    //quadrante Sw
    else if(qd->leaf.p.x >= p.x + (l/2) && qd->leaf.p.y < p.y + (l/2)){
                 printf("botRight\n");

          if(qd->quadrants[botRight] == NULL){

               qd->quadrants[botRight] = (QD_NODE *) malloc(l*l*sizeof(QD_NODE));
               qd->quadrants[botRight]->type = QDLEAF;
               qd->quadrants[botRight]->leaf.ocupied = false;
          }
          Point point = {p.x+(l/2),p.y};
      insertNode(qd,qd->quadrants[topRight], point, l/2);
    }



}

int searchQTP(QD_NODE* qd,Point exists,Point p,int l,int type){
     Point point  = add_Point(p,p);
     return searchQT(qd,exists,point,l*2,type);
}

int searchQT(QD_NODE* qd,Point exists,Point p,int l,int type){

     if(qd == NULL){
          return 0;
     }

     if(qd->type == QDLEAF){
          if(isEqual(qd->leaf.p,exists)){
               if(type == 1)
                    qd->leaf.value.state = PIECE_HITTED;
               if(type == 0)
                    qd->leaf.value.shotState = 1;
          }
          if(type == 3 && isEqual(qd->leaf.p,exists) )
               return  qd->leaf.value.state;
          if(type == 4 && isEqual(qd->leaf.p,exists) )
               return  qd->leaf.value.shotState;
          return 0;
     }
      if(exists.x < p.x + (l/2) && exists.y >= p.y + (l/2)){

        Point point = {p.x,p.y+(l/2)};

        return searchQT(qd->quadrants[topLeft],exists,point,l/2,type);

    }

    //quadrante NE
    else if(exists.x >= p.x + (l/2) && exists.y >= p.y + (l/2)){

          Point point = {p.x+(l/2),p.y+(l/2)};
          return searchQT(qd->quadrants[topRight],exists,point,l/2,type);
    }

    //quadrante SO
    else if(exists.x < p.x + (l/2) && exists.y < p.y + (l/2)){

          Point point = {p.x,p.y};
          return searchQT(qd->quadrants[botLeft],exists,point,l/2,type);
    }

    //quadrante Sw
    else if(exists.x >= p.x + (l/2) && exists.y < p.y + (l/2)){

      Point point = {p.x+(l/2),p.y};
          return searchQT(qd->quadrants[botRight],exists,point,l/2,type);
    }
}

QD_NODE* matrixToQUADT(Cell  matrix[40][40], int size ){
     QD_NODE *node = (QD_NODE*) malloc(size*size*sizeof(QD_NODE));
     node->type = QDLEAF;
     node->leaf.ocupied = false;
      Point mainPoint = make_Point(0,0);

     for(int i = 0; i < size; i++){
          for(int j = 0; j < size; j++){
               if(matrix[i][j].state != 0){
                    QD_NODE *n = (QD_NODE*) malloc(size*size*sizeof(QD_NODE));
                    n->type = QDLEAF;
                    n->leaf.value = matrix[i][j];
                    n->leaf.ocupied = true;
                    Point p = make_Point(j,i);
                    n->leaf.p = p;
                    insertNodeP(n,node,mainPoint,64);

               }
          }
     }
     return node;
}
void scanAndShotQ(QD_NODE *source,QD_NODE *target){
     Point mainPoint = make_Point(0,0);
     int x,y;
     puts("Escolha as coordenadas do tiro");
     scanf("%d",&x);
     scanf("%d",&y);

     //marcar tiro disparado na source
     Point point = make_Point(x,y);
          //se o nó não existe criamos um
     if(!searchQT(source,point,mainPoint,64,0)){ // 0 diz que é source

          Cell cell = {0,1};
          QD_NODE *node = (QD_NODE *) malloc(128*128*sizeof(QD_NODE));
          node->type = QDLEAF;
          node->leaf.ocupied = true;
          node->leaf.p = point;
          node->leaf.value = cell;

          insertNode(node,source,mainPoint,64);
     }


     //marcar a Cell que o tiro atinge

     if(!searchQT(target,point,mainPoint,64,1)){ // 1 diz que é target
          Cell cell = {PIECE_HITTED,0};
          QD_NODE *node = (QD_NODE *) malloc(128*128*sizeof(QD_NODE));
          node->type = QDLEAF;
          node->leaf.ocupied = true;
          node->leaf.p = point;
          node->leaf.value = cell;

          insertNode(node,target,mainPoint,64);

     }



}

void printQuad(QD_NODE* node, int size){

     printf("Os seus barcos\n");
     Point mainPoint = make_Point(0,0);

     for(int row = size -1; row >= 0; row--){
          for(int column = 0; column < size; column++){

               Point point = make_Point(column,row);
                switch (searchQTP(node,point,mainPoint,64,3)) //type igual a 3 não faz nada e retorna o state
               {
               case 0:
                    printf(BOLDBLUE);
                    printf(" ~ ");
                    break;

               case 1:
                    printf(BOLDWHITE);
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
     for (int i = 0; i < size; i++)
     {
          if (i >= 10)
               printf("%d ", i);
          else
               printf("%d  ", i);
     }
     puts("\n");

     for (int row = size-1; row >=0 ; row--)
     {
          printf(RED);
          if (row < 10)
               printf("%d  ", row);
          else
               printf("%d ", row);
          printf(RESET);

          for (int column = 0; column < size; column++)
          {
                Point point = make_Point(column,row);
               switch (searchQTP(node,point,mainPoint,64,4)) //retorna o shot state
               {
               case 0:
                    printf(BOLDBLUE);
                    printf(" ~ ");
                    break;

               default:
                    printf(BOLDRED);
                    printf(" X ");
                    break;

               }
          }
          printf(RESET);
          printf("\n");
     }

     puts("Prima n para continuar");
     char next = ' ';
     while (next != 'n')
     {
          scanf("%c", &next);
     }


}

int** quadToMatrix(QD_NODE* node, int size){
     int matriz[size][size];
     Point mainPoint = make_Point(0,0);
     for(int row = size -1; row >= 0; row--){
         for(int column = 0; column < size; column++){

              Point point = make_Point(column,row);
               matriz[row][column] = searchQTP(node,point,mainPoint,64,3); //type igual a 3 não faz nada e retorna o state

         }

    }


}
