#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include "table.h"



Player* readSharedMemory(int SHM_KEY){

   int shmid;
   shmid = shmget(SHM_KEY, sizeof(struct Player),IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
  
   }
   Player *p;
   // Attach to the segment to get a pointer to it.
   p = shmat(shmid, NULL, 0);
   if (p == (void *) -1) {
      perror("Shared memory attach");
    
   }
   
  


   printf("Reading Process: Complete\n");
   return p;
}
int closeSharedMemory(Player *p){
    if (shmdt(p) == -1) {
      perror("shmdt");
      return 1;
   }
}