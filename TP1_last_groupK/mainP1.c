#include <stdio.h>
#include <stdlib.h>
#include "table.h"


#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include			<sys/sem.h>


int size = 0;
Player *p2_shared;
Player *p1_shared;
char* path_1="./p1Config.txt";
char* path_2="./p2Config.txt";
int semaphore_id_controle_p2;
int semaphore_id_controle_p1;

int main()
{



     //creating a semaphore
     int semaphore_id;
	if ((semaphore_id = semget(1, 1, IPC_CREAT)) == -1) {
	 		puts("error");

	}

	if ((semaphore_id_controle_p1 = semget(2, 1, IPC_CREAT)) == -1) {
	 		puts("error");

	}

	if ((semaphore_id_controle_p2 = semget(3, 1, IPC_CREAT)) == -1) {
	 		puts("error");

	}

     int semaphore_id_qualPlayer;
	if ((semaphore_id_qualPlayer = semget(4, 1, IPC_CREAT)) == -1) {
	 		puts("error");

	}
     int valorSize;
	if ((valorSize = semget(5, 1, IPC_CREAT)) == -1) {
	 		puts("error");

	}






     printf("valor do semaforo %d\n", semctl(semaphore_id_qualPlayer, 0, GETVAL,0));




    srand(time(0));
     printf("\033[01;33m"); // bold yellow
     printf("     ____        _   _   _           _     _                  \n");
     printf("    | __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __             \n");
     printf("    |  _ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\            \n");
     printf("    | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |           \n");
     printf("    |____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/            \n");
     printf("                                            |_|               \n");
     printf("\033[0m");
     if(semctl(semaphore_id_qualPlayer, 0, GETVAL,0)==1 || semctl(semaphore_id_qualPlayer, 0, GETVAL,0)==0){
          semctl(semaphore_id_controle_p1, 0, SETVAL,0);


          semctl(semaphore_id_qualPlayer, 0, SETVAL,2);


          puts("Escolha o tamanho do tabuleiro 20-40");
          scanf("%d", &size);
          semctl(valorSize, 0, SETVAL,size);
          puts("Usar matriz(0) ou QuadTree(1)");
          int quad;
          scanf("%d",&quad);
          puts("Criar barcos aleatorios ? 1/0");

          int random;

          scanf("%d", &random);

          //  ------------- teste ----------------

          Player p1 = {0, 0, malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100)};
          p1.root =(QD_NODE*) malloc(size*size*sizeof(QD_NODE));
          p1.root->type = QDLEAF;
          p1.root->leaf.ocupied = false;

          puts("digite Seu nome");
          scanf("%s",p1.name);
          puts("primeiro jogador escolhendo navios");
          initializeMatriz(&p1, size);
          chooseShips(&p1, random,size);

          if(quad){
               p1.root  = matrixToQUADT(p1.matriz,size);
          }

          int op;
          puts("digite a forma de comunicação entre terminais que vc  deseja usar \n 1 :  para inter-processcommunication \n 2 : para semaphores");
           scanf("%d", &op);

          switch (op)
          {
          case 1:


               p1.ID_P=2;


               //compartilhando player p1
               int shmt =writeSharedMemory(p1,0x1234);
               //iniciando players compartilhados
               p2_shared=readSharedMemory(0x4567);
               p1_shared=readSharedMemory(0x1234);


               int aux_p1=0, aux_p2=0;
               while(! (aux_p1==2 && aux_p2==2)){
                    aux_p1=p1_shared->ID_P;
                    aux_p2=p2_shared->ID_P;
                    if(aux_p1!=2){
                         puts("a espera do jogador 1");
                    }
                    if(aux_p2!=2){
                         puts("a espera do jogador 2");
                    }
                    sleep(3);

               }
               printf(RED);
               puts("Pronto para iniciar o jogo");
               printf(RESET);
               p2_shared->ID_P=0;
               p1_shared->ID_P=1;
               startGame(p1_shared,p2_shared,shmt);



               break;

          case 2:
               puts("fdihwpoihrpf");
               write_conf(path_1,&p1);
               semctl(semaphore_id_controle_p1, 0, SETVAL,1);
               Player p_para_leitura= {0, 0, malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100),0};
               while(semctl(semaphore_id_controle_p2, 0, GETVAL)!=1){
                    puts("terminar a escrita do p2 para ler");
                    printf("%d\n",semctl(semaphore_id_controle_p2, 0, GETVAL));
                    sleep(2);
               }


               read_conf(path_2,&p_para_leitura);
               semctl(semaphore_id, 0, SETVAL,1);
               startGameNoShared(&p1,&p_para_leitura,semaphore_id,quad);
               if (semctl (semaphore_id, 0, IPC_RMID) == -1) {
                    puts ("semctl IPC_RMID");
               }
              if (semctl (semaphore_id_controle_p2, 0, IPC_RMID) == -1) {
                    puts ("semctl IPC_RMID");
               }
              if (semctl (semaphore_id_controle_p1, 0, IPC_RMID) == -1) {
                    puts ("semctl IPC_RMID");
               }



               break;
          }



     }else{

          semctl(semaphore_id_controle_p2, 0, SETVAL,0);

          semctl(semaphore_id_qualPlayer, 0, SETVAL,1);
          puts("Usar matriz(0) ou QuadTree(1)");
          int quad;
          scanf("%d",&quad);


          puts("Criar barcos aleatorios ? 1/0");

          int random;

          scanf("%d", &random);
          //  ------------- teste ----------------


          Player p2 = {0, 0, malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100)};
          p2.root =(QD_NODE*) malloc(size*size*sizeof(QD_NODE));
          p2.root->type = QDLEAF;
          p2.root->leaf.ocupied = false;

          puts("digite Seu nome");
          scanf("%s",p2.name);
          puts("primeiro jogador escolhendo navios");
          int tamanhoTabuleiro = semctl(valorSize, 0, GETVAL,0);
          printf("O tamanho do tabuleiro %d\n",tamanhoTabuleiro);
          initializeMatriz(&p2,tamanhoTabuleiro);
          chooseShips(&p2, random,tamanhoTabuleiro);

          if(quad){
               p2.root = matrixToQUADT(p2.matriz,size);
          }


          int op;
          puts("digite a forma de comunicação entre terminais que vc  deseja usar \n 1 :  para inter-processcommunication \n 2 : para semaphores");
          scanf("%d", &op);

          switch (op)
          {
          case 1:


               p2.ID_P=2;

               //compartilhar p2
               int shmt =writeSharedMemory(p2,0x4567);
               //iniciar shared players
               p2_shared=readSharedMemory(0x4567);
               p1_shared=readSharedMemory(0x1234);

               int aux_p1=0, aux_p2=0;
               while(! (aux_p1==2 && aux_p2==2)){
                    aux_p1=p1_shared->ID_P;
                    aux_p2=p2_shared->ID_P;
                    if(aux_p1!=2){
                         puts("a espera do jogador 1");
                    }
                    if(aux_p2!=2){
                         puts("a espera do jogador 2");
                    }
                    sleep(3);
               }
               printf(RED);
               puts("Pronto para iniciar o jogo");
               printf(RESET);
               p2_shared->ID_P=0;
               startGameP2(p1_shared,p2_shared,shmt);

               break;

          case 2:
               write_conf(path_2,&p2);
               semctl(semaphore_id_controle_p2, 0, SETVAL,1);

               printf("semaforo %d\n",semctl(semaphore_id_controle_p1, 0, GETVAL));
               while(semctl(semaphore_id_controle_p1, 0, GETVAL)!=1){
                    puts("aguardando terminar a escrita do p1 para ler");
                    sleep(2);
               }



               Player p_para_leitura= {0, 0, malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100),0};

               read_conf(path_1,&p_para_leitura);



               startGameNoSharedP2(&p_para_leitura,&p2,semaphore_id,tamanhoTabuleiro,quad);
               if (semctl (semaphore_id, 0, IPC_RMID) == -1) {
                    puts ("semctl IPC_RMID");
               }

              if (semctl (semaphore_id_controle_p2, 0, IPC_RMID) == -1) {
                    puts ("semctl IPC_RMID");
               }
              if (semctl (semaphore_id_controle_p1, 0, IPC_RMID) == -1) {
                    puts ("semctl IPC_RMID");
               }



               break;

          }


     }








     return 0;
}




void startGameNoSharedP2(Player *p1, Player *p2,int semaphore_id,int size,int quad)
{    semctl(semaphore_id, 0, SETVAL,1);
     int counter = 0;
     system("clear");
     while (1)
     {
          if(semctl(semaphore_id, 0, GETVAL)==2){

               if (quad) {
                    Point mainPoint = make_Point(0,0);
                    //construir matriz a partir de quad tree
                    int matrix[size][size];
                    for(int row = size -1; row >= 0; row--){
                        for(int column = 0; column < size; column++){

                             Point point = make_Point(column,row);
                              matrix[row][column] = searchQTP(p2->root,point,mainPoint,64,3); //type igual a 3 não faz nada e retorna o state

                        }

                   }
                    read_conf(path_2,p2);  //fazer para quad
                    puts("Sua vez de Jogar");

                    sleep(1);
                    //enter para aparecer tabelas player 2
                    //print board barcos player 2 e tiros player 2
                    printQuad(p2->root, size);
                    scanAndShotQ(p2->root,p1->root);

                    write_conf(path_1,p1);
                    write_conf(path_2,p2);
                    system("clear");
                    printQuad(p2->root,size);
                    semctl(semaphore_id, 0, SETVAL,1);



               }else{



               read_conf(path_2,p2);
               puts("Sua vez de Jogar");

               sleep(1);
               //enter para aparecer tabelas player 2
               //print board barcos player 2 e tiros player 2
               print_table(p2, 0, size);

               // p2 scan target
               printf("total peças p2 %d \n",p2->total_pieces);
               printf("total peças p1 %d \n",p1->total_pieces);
               if (ScanAndShot(p2, p1))
               { //target
                    return;
               }
               write_conf(path_1,p1);
               write_conf(path_2,p2);
               system("clear");
               print_table(p2, 1, size);
               semctl(semaphore_id, 0, SETVAL,1);
          }

          }else{


               switch (counter)
               {
               case 0:
                system("clear");

                  puts("Aguarde sua vez.");
                  counter++;
                    break;
               case 1:
                system("clear");
                    puts("Aguarde sua vez..");
                    counter++;
                    break;
               case 2:
                system("clear");
                    puts("Aguarde sua vez...");
                    counter=0;
                    break;

               }

               sleep(1);
          }




     }




}


void startGameP2(Player *p1, Player *p2,int shmt)
{
     int counter = 0 ;
     while (1)
     {
          if(p2->ID_P==1){

               puts("dentro p2");
               sleep(1);
               //enter para aparecer tabelas player 2
               //print board barcos player 2 e tiros player 2
               print_table(p2, 0, size);

               // p2 scan target
               printf("total peças p2 %d \n",p2->total_pieces);
               printf("total peças p1 %d \n",p1->total_pieces);
               if (ScanAndShot(p2, p1))
               { //target
                    return;
               }
               //clear
               //printfeedback
               //print tabelas atualizadas

               print_table(p2, 1, size);
               system("clear");
               //enter para desaparecer tabelas player 2
               p1->ID_P=1;
               p2->ID_P=0;
          }else{
               switch (counter)
               {
               case 0:
                system("clear");
                  puts("Aguarde sua vez.");
                  counter++;
                    break;
               case 1:
                system("clear");
                    puts("Aguarde sua vez..");
                    counter++;
                    break;
               case 2:
                system("clear");
                    puts("Aguarde sua vez...");
                    counter=0;
                    break;

               }

               sleep(1);
          }
     }


     //fechando shared players
     closeWriteSharedMemory(shmt);
     closeSharedMemory(p2_shared);
     closeSharedMemory(p1_shared);

}




void startGameNoShared(Player *p1, Player *p2,int semaphore_id,int quad)
{      int counter = 0;

     semctl(semaphore_id, 0, SETVAL,1);
     while (1)
     {
          if (quad) {


                    Point mainPoint = make_Point(0,0);
                    //construir matriz a partir de quad tree
                    int matrix[size][size];
                    for(int row = size -1; row >= 0; row--){
                        for(int column = 0; column < size; column++){

                             Point point = make_Point(column,row);
                              matrix[row][column] = searchQTP(p1->root,point,mainPoint,64,3); //type igual a 3 não faz nada e retorna o state

                        }
                   }



               read_conf(path_1,p1);
               puts("Sua vez de Jogar");

               sleep(1);
               //enter para aparecer tabelas player 2
               //print board barcos player 2 e tiros player 2
               printQuad(p2->root, size);
               scanAndShotQ(p1->root,p2->root);

               write_conf(path_2,p2);
               write_conf(path_1,p1);
               system("clear");
               printQuad(p1->root,size);
               semctl(semaphore_id, 0, SETVAL,1);



          }else{

               if(semctl(semaphore_id, 0, GETVAL)==1){
                    read_conf(path_1,p1);
                    puts("Sua vez de Jogar");
                    sleep(1);
                    //enter para aparecer tabelas player 2
                    //print board barcos player 2 e tiros player 2
                    print_table(p1, 0, size);

                    // p2 scan target
                    printf("total peças p2 %d \n",p2->total_pieces);
                    printf("total peças p1 %d \n",p1->total_pieces);
                    if (ScanAndShot(p1, p2))
                    { //target
                         return;
                    }
                    system("clear");
                    write_conf(path_2,p2);
                    write_conf(path_1,p1);
                    print_table(p1, 1, size);
                    semctl(semaphore_id, 0, SETVAL,2);

               }else{
                    switch (counter)
                    {
                    case 0:
                    system("clear");
                       puts("Aguarde sua vez.");
                       counter++;
                         break;
                    case 1:
                     system("clear");
                         puts("Aguarde sua vez..");
                         counter++;
                         break;
                    case 2:
                     system("clear");
                         puts("Aguarde sua vez...");
                         counter=0;
                         break;

                    }

                    sleep(1);
               }
          }


     }




}


void startGame(Player *p1, Player *p2,int shmt)
{
     int counter = 0 ;
     while (1)
     {
          if(p1->ID_P==1){

               puts("dentro p1");
               sleep(1);
               //enter para aparecer tabelas player 1
               // print board barcos player 1 e tiros player 1
               print_table(p1, 0, size);
               // p1 scan target
               printf("total peças p2 %d \n",p2->total_pieces);
               printf("total peças p1 %d \n",p1->total_pieces);
               if (ScanAndShot(p1, p2))
               { //target
                    return;
               }

               //clear

               //print feedback
               // print tabelas atualizadas
               print_table(p1, 1, size);
               //enter para desaparecer tabelas player 1
               system("clear");
               p1->ID_P=0;
               p2->ID_P=1;
          }else{
               switch (counter)
               {
               case 0:
               system("clear");
                  puts("Aguarde sua vez.");
                  counter++;
                    break;
               case 1:
                system("clear");
                    puts("Aguarde sua vez..");
                    counter++;
                    break;
               case 2:
                system("clear");
                    puts("Aguarde sua vez...");
                    counter=0;
                    break;

               }

               sleep(1);
          }




     }


   //fechando compartilhamento de players
     closeWriteSharedMemory(shmt);
     closeSharedMemory(p2_shared);
     closeSharedMemory(p1_shared);



}

void chooseShips(Player *player, int random,int size)
{

     int amount = 0, n_ships = 0, total_ships = 0;
     n_ships = 4;

     player->myShips = malloc(sizeof(Node) * size);

     for (int i = 0; i < n_ships; i++)
     {
          int n_ships_type = 0;

          switch (i)
          {
          case 0:
               puts("Escolhendo posições do barco no formato de 'T' ocupa 3 peças horizontais e 2 verticais");
               break;
          case 1:
               puts("Escolhendo posições do barco no formato de 'L' ocupa 3 peças horizontais e 2 verticais");
               break;
          case 2:
               puts("Escolhendo posições do barco no formato de 'I' ocupa 3 peças verticais");

               break;
          case 3:
               puts("Escolhendo posições do barco no formato de 'Z' ocupa 3 peças horizontais na parte superior 2 na diagonal e 3 peças horizontais na parte inferior");

               break;
          default:
               break;
          }
          puts("escolha a quantidade de barcos desse tipo");
          int test = 0;

          do
          {

               if (random)
               {

                    n_ships_type = randomN(1, 3);
                    printf("quandtidade de barcos %d\n", n_ships_type);
               }
               else
               {

                    test = 0;
                    scanf("%d", &n_ships_type);
               }

               if (n_ships_type <= 0 || (n_ships_type + (total_ships)) < ((size * size) / 25) && (n_ships_type > ((size * size) / 25) - 4 + i))
               {
                    puts("numero de barcos invalido, ou foi menor que zero ou excedeu número maximo de barcos");
                    test = 1;
               }

          } while (test);


          for (int o = 0; o < n_ships_type; o++)
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
                    if (random){

                         row = randomN(0, size - 1);
                         col = randomN(0, size - 1);
                         printf("%d linha \n ", row);
                         printf("%d coluna \n", col);
                    }
                    else
                    {
                         printf("Defina a linha e coluna para colocar o barco de nº %d ex: X Y \n ", i);

                         scanf("%d", &row);
                         scanf("%d", &col);
                    }

                    flag = 0;

                    for (int i = row; i < row + 3; i++)
                    {
                         for (int j = col; j < col + 3; j++)
                         {
                              if (i < size && j < size)
                                   if (player->matriz[i][j].state != 0)
                                   {
                                        printf("peças de barcos em [%d][%d]\n", i, j);
                                        flag = 1;
                                   }
                         }
                    }

                    if (flag == 0)
                    {
                         if (random)
                         {
                              rotate = randomN(0, 3) * 90;
                              printf("%d rotate \n", rotate);
                         }
                         else
                         {
                              puts("Defina a rotação do barco");

                              scanf("%d", &rotate);
                         }

                         switch (i)
                         {
                         case 0:
                              switch (rotate)
                              {
                              case 0:
                                   if (col + 2 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (row + 2 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 90:
                                   if (row - 1 < 0)

                                        if (col + 2 > size)
                                        {
                                             puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                             flag = 1;
                                        }
                                   if (row + 1 >= size)
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
                                   if (col + 2 >= size)
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
                                   if (row + 1 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (col + 2 >= size)
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
                                   if (row + 3 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (col + 3 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;

                              case 90:
                                   if (row + 2 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (col + 3 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 180:
                                   if (row + 2 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (col + 2 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 270:
                                   if (col + 2 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (row + 2 >= size)
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
                                   if (row + 3 > size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 90:
                                   if (col + 3 > size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 180:
                                   if (row + 3 > size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 270:
                                   if (col + 3 > size)
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
                                   if (col + 3 > size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (row + 3 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 90:
                                   if (row + 3 > size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (col + 3 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 180:
                                   if (col + 3 > size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (row + 3 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              case 270:
                                   if (row + 3 > size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   if (col + 3 >= size)
                                   {
                                        puts("invalida rotação nessa posição a pesça saira do tabuleiro");
                                        flag = 1;
                                   }
                                   break;
                              }
                         }
                    }
                    else
                    {
                         puts("sobreposição de barcos porfavor escolher outra posição");
                    }
               } while (flag);

               player->myShips[i].gravity_point_row = row;
               player->myShips[i].gravity_point_col = col;
               player->myShips[i].rotate = rotate;
               player->myShips[i].value.type = i;
               player->myShips[i].amount = amount;
               player->myShips[i].index = i;
               putSingleShip(player, i);
               printf("numero de barcos %d\n", player->activeShips);

               print(player, size);
          }

     }
}
