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
  
//a shared memory object should be identified by a name of the form /somename;
constexpr const char* key = "/sharememory"; 



int main()
{
    int fd = shm_open(key, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);     // Create the shared memor object with the given key
                                                                     // The object allows to be read or written and also has the permission for the current user is read and write

    if (fd == -1)
    {
        fprintf(stderr, "Error when creating share memory %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Because when we create THE SHARED OBJECT, the size of it equals zero
    // Thus needing to invoke truncate. The truncate by its meaning will reduce the size
    // but in this case, it will increase. Here we increase the size of it to 4096 (Frame)

    if (ftruncate(fd, 4096) == -1)
    {
        fprintf(stderr, "Extend the size of memory failed %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }


    // Map the share object to the virtual address space of the current process
    // We speicify the operations are read and write. And also, to make any changes happened in this process
    // affects other, we HAVE to explicitly set MAP_SHARED. Otherwise, it will limit inside the current process

    void* ptr = mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED)
    {
        fprintf(stderr, "Mapping the shared object into the virtual address space failed %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    uint8_t* buffer = (uint8_t*)ptr;

    char message[]= "Hello";

    // Copy our data into the share memory and allow other process to read from it

    memcpy(buffer, message, sizeof(message));

    // Don't forget to unmap the shared memory segment after using it. This is a good habit

    munmap(buffer, 4096);
    
}

