#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "table.h"


Player *p_teste;
int writeSharedMemory(Player player , int SHM_KEY) {
   int shmid;
   shmid = shmget(SHM_KEY, sizeof(Player), IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   
   // Attach to the segment to get a pointer to it.
   p_teste = shmat(shmid, NULL, 0);
   if (p_teste == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }
     
/* Transfer blocks of data from buffer to shared memory */
   // copiando to ready
   p_teste->ID_P=player.ID_P;
   //copiando matriz
   for (int i  = 0; i < 40; i++) {
            for (int j = 0; j < 40; j++) {
                p_teste->matriz[i][j]=player.matriz[i][j];
                p_teste->matriz[i][j].state = player.matriz[i][j].state;
                p_teste->matriz[i][j].shotState = player.matriz[i][j].shotState;

            }
    }
   //copiando barcos
   p_teste->myShips = malloc(sizeof(Node) * 100);
     for (int i  = 0; i < 100; i++) {
        p_teste->myShips[i]=player.myShips[i];
     }
   //copiando nome
      p_teste->name = malloc(sizeof(char) * 50);
      for (int i  = 0; i < 50; i++) {
         p_teste->name[i]=player.name[i];
     }
     p_teste->activeShips = player.activeShips;
     p_teste->total_pieces = player.total_pieces;


   printf("Writing Process: Complete\n");
   return shmid;
}
int closeWriteSharedMemory(int shmid){

      if (shmdt(p_teste) == -1) {
      perror("shmdt");
      return 1;
   }

   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      return 1;
   }
}