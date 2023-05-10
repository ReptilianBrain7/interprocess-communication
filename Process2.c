#include "Process.h"

char buffer[BUF_SIZE];

int main(int argc, char* argv[])
{
  int fd = shm_open("/test", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  shm *shared_memory = mmap(NULL, sizeof(shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  do
  {
    sem_wait(&shared_memory->sem1_);
    strcpy(buffer, shared_memory->buf);
    printf("Hey pal, got your message. I will read it out loud.\n");
    
    for(int i = 0; i < sizeof(buffer); i++)
    {
      printf("%c", buffer[i]);
    }

    printf("Btw, there is a number stored in the shared quantum space\n");
    printf("This is the number: %d", shared_memory->number_);

    sem_post(&shared_memory->sem2_);

  } while (strcmp(shared_memory->buf, "bye\n") != 0);


}