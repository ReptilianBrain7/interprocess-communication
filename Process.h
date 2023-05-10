#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

int process_id;

typedef struct shm
{
  sem_t sem1_;
  sem_t sem2_;
  int number_;
  char buf[BUF_SIZE];
} shm;