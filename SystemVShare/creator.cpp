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
    int shmid = shmget(shmkey,1024, 0600 | IPC_CREAT);

    printf("The key is 0X%x\n", shmid);

    void *ptrToShared = shmat(shmid,NULL,0);

    if (ptrToShared == (void*)-1)
    {
        fprintf(stderr,"Attach share memory segment failed %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char *shmpointer = (char*)ptrToShared;

    printf("Write data into shared memory\n");

    char buffer[] = "Shared data";

    memcpy(shmpointer, buffer, sizeof(buffer));

    shmdt(&shmpointer);

    // shmctl(shmid, IPC_RMID, NULL);
}  