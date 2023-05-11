#include "Process.h"

char buffer[BUF_SIZE];

int getCommand(char *buffer) {
  memset(buffer, 0, BUF_SIZE * sizeof(char));
  if (fgets(buffer, BUF_SIZE * sizeof(char), stdin) != NULL) {
    return 1;
  }
  else
    return 0;
}

int main(int argc, char* argv[])
{
  int fd = shm_open("/test", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  ftruncate(fd, sizeof(shm));
  shm *shared_memory = mmap(NULL, sizeof(shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  sem_init(&shared_memory->sem1_, 1, 0);
  sem_init(&shared_memory->sem2_, 1, 0);

  process_id = fork();
  if (process_id == 0)
  {
    char* arg_list[] = {"Process2", NULL};
    execv("Process2", arg_list);
  }

  do
  {
    printf("Process1 ready for some action.\n");
    int control = getCommand(buffer);
    if (control == 0)
      strcpy(buffer, "bye\n");
    strcpy(shared_memory->buf, buffer);
    printf("Here, buddy. I wrote you something.\n");
    sem_post(&shared_memory->sem1_);
    sem_wait(&shared_memory->sem2_);

    fflush(stdin);
    
  } while (strcmp(buffer, "bye\n") != 0);

  printf("Process1 is done\n");

  sem_destroy(&shared_memory->sem1_);
  sem_destroy(&shared_memory->sem2_);

  munmap(shared_memory, sizeof(shm));

  shm_unlink("/test");
}