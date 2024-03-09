#include <iostream>
#include <sys/ipc.h>     // only needs for system V shared memory
#include <sys/shm.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


constexpr int shmkey = 22222;

int main()
{
    // Create a shared object using a unique key
    // If the shared object not exists, system creates new one
    // 0600 is the permission for user,group,other
    int shmid = shmget(shmkey,1024, 0600 | IPC_CREAT);

    printf("The key is 0X%x\n", shmid);

    // attach the shared object to the virtual address space

    char *shmpointer = (char*)shmat(shmid,NULL,0);

    printf("Read data from shared memory\n");

    char buffer[4096];

    memcpy(buffer,shmpointer , sizeof(buffer));

    printf("Content: %s\n", buffer);

    // Detach after finishing

    shmdt(&shmpointer);

    // Remove the shared object

    shmctl(shmid, IPC_RMID, NULL);
}  