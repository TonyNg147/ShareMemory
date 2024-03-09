#include <iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

constexpr const char* key = "/sharememory";  

int main()
{

    int fd = shm_open(key, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);    // Create the shared memor object with the given key
                                                                     // The object allows to be read or written and also has the permission for the current user is read and write

    if (fd == -1)
    {
        fprintf(stderr, "Error when creating share memory %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Because we expand the size of the Shared memory object in the creator. Thus no need to call it here

    void* ptr = mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (ptr == MAP_FAILED)
    {
        fprintf(stderr, "Mapping the shared object into the virtual address space failed %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char buffer[4096];

    // Copy the content from the shared memory to our buffer and display it

    memcpy(buffer,ptr, 4096);

    printf("Content is %s\n", buffer);

    munmap(buffer, 4096);

    shm_unlink(key);

}