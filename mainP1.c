#include <stdio.h>
#include <stdlib.h>
#include "table.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/sem.h>

int size = 0;
int quad = 0;
Player *p2_shared;
Player *p1_shared;
char *path_1 = "./p1Config.txt";
char *path_2 = "./p2Config.txt";
int main()
{

     //creating a semaphore
     int semaphore_id;
     if ((semaphore_id = semget(1, 1, IPC_CREAT)) == -1)
     {
          puts("error");
     }

     int semaphore_id_controle_p1;
     if ((semaphore_id_controle_p1 = semget(2, 1, IPC_CREAT)) == -1)
     {
          puts("error");
     }

     int semaphore_id_controle_p2;
     if ((semaphore_id_controle_p2 = semget(3, 1, IPC_CREAT)) == -1)
     {
          puts("error");
     }

     int boardSize;
     if ((boardSize = semget(4, 1, IPC_CREAT)) == -1)
     {
          puts("error");
     }

     int communication;
     if ((communication = semget(5, 1, IPC_CREAT)) == -1)
     {
          puts("error");
     }
     int readyTOstart;
     if ((readyTOstart = semget(6, 1, IPC_CREAT)) == -1)
     {
          puts("error");
     }

     semctl(semaphore_id_controle_p1, 0, SETVAL, 0);
     semctl(readyTOstart, 0, SETVAL, 0);

     srand(time(0));
     printf("\033[01;33m"); // bold yellow
     printf("     ____        _   _   _           _     _                  \n");
     printf("    | __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __             \n");
     printf("    |  _ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\            \n");
     printf("    | |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |           \n");
     printf("    |____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/            \n");
     printf("                                            |_|               \n");
     printf("\033[0m");
     puts("Escolha o tamanho do tabuleiro 20-40");
     scanf("%d", &size);
     semctl(boardSize, 0, SETVAL, size);

     puts("Criar barcos aleatorios ? 1/0");

     int random;

     scanf("%d", &random);

     //  ------------- teste ----------------

     Player p1 = {0, 0, malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100)};
     p1.tree = quadtree_new(0, 0, 40, 40);
     puts("digite Seu nome");
     scanf("%s", p1.name);
     puts("primeiro jogador escolhendo navios");
     initializeMatriz(&p1, size);
     chooseShips(&p1, random);

     int op;
     puts("digite a forma de comunicação entre terminais que vc  deseja usar \n 1 :  para inter-processcommunication \n 2 : para semaphores");
     scanf("%d", &op);
     semctl(communication, 0, SETVAL, op);

     switch (op)
     {
     case 1:
          semctl(readyTOstart, 0, SETVAL, 1);

          p1.ID_P = 2;

          //compartilhando player p1
          int shmt = writeSharedMemory(p1, 10);
          //iniciando players compartilhados
          p2_shared = readSharedMemory(11);
          p1_shared = readSharedMemory(10);
          int counter = 0;
          int aux_p1 = 0, aux_p2 = 0;
          while (!(aux_p1 == 2 && aux_p2 == 2))
          {
               aux_p1 = p1_shared->ID_P;
               aux_p2 = p2_shared->ID_P;

               if (aux_p2 != 2)
               {

                    switch (counter)
                    {
                    case 0:
                         system("clear");
                         puts("Aguarde o player 2.");
                         counter++;
                         break;
                    case 1:
                         system("clear");
                         puts("Aguarde o player 2..");
                         counter++;
                         break;
                    case 2:
                         system("clear");
                         puts("Aguarde o player 2...");
                         counter = 0;
                         break;
                    }
                  
                    sleep(1);

               }
          }
          printf(RED);
          puts("Tudo Pronto para Iniciar");
          printf(RESET);
          p2_shared->ID_P = 0;
          p1_shared->ID_P = 1;
          startGame(p1_shared, p2_shared, shmt);

          break;

     case 2:
          semctl(readyTOstart, 0, SETVAL, 1);

          puts("Deseja usar quadTree ? \n yes-> 1 \n No-> 0 ");
          scanf("%d", &quad);

          if (quad)
          {
               switchMatrizToQuad(&p1);
          }

          write_conf(path_1, &p1, quad);
          semctl(semaphore_id_controle_p1, 0, SETVAL, 1);
          Player p_para_leitura = {0, 0, malloc(sizeof(char) * 50), malloc(sizeof(Node) * 100), 0};
          p_para_leitura.tree = quadtree_new(0, 0, 40, 40);
          while (semctl(semaphore_id_controle_p2, 0, GETVAL) != 1)
          {
               switch (counter)
               {
               case 0:
                    system("clear");
                    puts("Aguarde o player 2.");
                    counter++;
                    break;
               case 1:
                    system("clear");
                    puts("Aguarde o player 2..");
                    counter++;
                    break;
               case 2:
                    system("clear");
                    puts("Aguarde o player 2...");
                    counter = 0;
                    break;
               }

               sleep(1);
          }

          read_conf(path_2, &p_para_leitura, quad);
          startGameNoShared(&p1, &p_para_leitura, semaphore_id);
          if (semctl(semaphore_id, 0, IPC_RMID) == -1)
          {
               puts("semctl IPC_RMID");
          }
          if (semctl(semaphore_id_controle_p2, 0, IPC_RMID) == -1)
          {
               puts("semctl IPC_RMID");
          }
          if (semctl(semaphore_id_controle_p1, 0, IPC_RMID) == -1)
          {
               puts("semctl IPC_RMID");
          }

          break;
     }

     return 0;
}

void startGameNoShared(Player *p1, Player *p2, int semaphore_id)
{
     int counter = 0;
     semctl(semaphore_id, 0, SETVAL, 1);
     while (1)
     {
          if (semctl(semaphore_id, 0, GETVAL) == 1)
          {
               read_conf(path_1, p1, quad);
               puts("Sua vez de Jogar");
               sleep(1);
               //enter para aparecer tabelas player 2
               //print board barcos player 2 e tiros player 2
               print_table(p1, 0, size);

               // p2 scan target
               printf("total peças p2 %d \n", p2->total_pieces);
               printf("total peças p1 %d \n", p1->total_pieces);
               if (ScanAndShot(p1, p2))
               { //target
                    return;
               }
               system("clear");
               write_conf(path_2, p2, quad);
               write_conf(path_1, p1, quad);
               print_table(p1, 1, size);
               semctl(semaphore_id, 0, SETVAL, 2);
          }
          else
          {
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
                    counter = 0;
                    break;
               }

               sleep(1);
          }
     }
}

void startGame(Player *p1, Player *p2, int shmt)
{
     int counter = 0;
     while (1)
     {
          if (p1->ID_P == 1)
          {

            
               sleep(1);
               //enter para aparecer tabelas player 1
               // print board barcos player 1 e tiros player 1
               print_table(p1, 0, size);
               // p1 scan target
               printf("total peças p2 %d \n", p2->total_pieces);
               printf("total peças p1 %d \n", p1->total_pieces);
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
               p1->ID_P = 0;
               p2->ID_P = 1;
          }
          else
          {
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
                    counter = 0;
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

void chooseShips(Player *player, int random)
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
                    if (random)
                    {
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
