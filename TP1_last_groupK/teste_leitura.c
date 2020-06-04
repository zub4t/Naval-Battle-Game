#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include "table.h"

#define BUF_SIZE 1024
#define SHM_KEY 1

int main(int argc, char const *argv[])
{
    int shmid;
    Player *shmp;
    shmp=readSharedMemory(0x1234);
     printf(" memoria  %d \n",shmp);
    printf("id relacionado %d \n",shmp->ID_P);
    closeSharedMemory(shmp);
    return 0;
}
