#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include "msg_data.h"

int main()
{   //map 관련 함수는 말 그대로 해당 주소의 memory에 원하는 data를 저장한다거나... 
    int i;
    const char* name = "SHM_TEST";                  // Name of the shared memory object    
    int shm_fd;                                     // File descriptor for shared memory
    void* shmPointer;                               // Pointer to shared memory object
    int messageSize = sizeof(messageStruct);        // Size of message
    
    messageStruct messageToRead[MESSAGE_TOTAL] = {};
     
    /* Create the shared memory object */
    //api function offer POSIX standard
    // shared_memory name:SHM_TEST, open flag, access
    // open flag : create or read+write 
    shm_fd = shm_open(name, O_RDONLY, 0666);
    
    
    /* Configure the size of the shared memory object */
    // size of shared memory 
    // if (ftruncate(shm_fd, messageSize*MESSAGE_TOTAL) == -1) {
    //     printf("ftruncate failed.\n");
    //     return -1;
    // }
 
    /* Map the shared memory object */
    //커널에게 파일을 0에 mapping해라... MESSAGE_TOTAL만큼 맵핑
    shmPointer = (unsigned char*)mmap(0, messageSize*MESSAGE_TOTAL, PROT_READ, MAP_SHARED, shm_fd, 0);
    
    /* Write messages into the shared memory object */
    //dest, source, size
    for (i = 0; i < MESSAGE_TOTAL; i++) {
        memcpy(&messageToRead[i], shmPointer + messageSize*i, messageSize);
    }
         
    /* Unmap shared memory */
    //shmPointer에서 시작하는 process address space에 위치한 page를 포함하는 모든 mapping 제거... MESSAGE_TOTAL byte만큼 이어져서...
    munmap(shmPointer, messageSize*MESSAGE_TOTAL);
    
    /* Close shared memory communication */
    close(shm_fd);
    if(shm_unlink(name)==-1){
        printf("shm_unlink failed.\n");
        return -1;
    }
    for (i = 0; i < MESSAGE_TOTAL; i++) {
        printf("Read %s and %f into %dth area.\n", messageToRead[i].name, messageToRead[i].value,i);
    }

    return 0;
}