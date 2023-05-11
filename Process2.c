#include "Process.h"

char *dispatcher(shm *shared_memory);

// This char array called "predefines" has been copied over from the Assginemt Framework
char* predefines[] = {                          //     motivated answer        unmotivated answer
        "Do I love programming?\n",           //0    "Oh yes!\n"     (12)    "Maybe.\n"      (9)
        "Should I drink some beer?\n",        //1    "Maybe.\n"      (9)     "Definitely!\n" (11)
        "Will I pass SLP?\n",                 //2    "Definitely!\n" (11)    "Maybe.\n"      (9)
        "Should I use locking?\n",            //3    "Definitely!\n" (11)    "Definitely!\n" (11)
        "Should I take a break?\n",           //4    "No.\n"         (10)    "Oh yes!\n"     (12)
        "Should I copy code?\n",              //5    "No.\n"         (10)    "No.\n"         (10)
        "bye\n",                              //6
        "motivation\n",                       //7
        "unmotivation\n",                     //8
        "Maybe.\n",                           //9
        "No.\n",                              //10
        "Definitely!\n",                      //11
        "Oh yes!\n",                          //12
        "I do not know.\n"                    //13
};

char request[BUF_SIZE];
char response[BUF_SIZE];

int main(int argc, char* argv[])
{
  int fd = shm_open("/test", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  shm *shared_memory = mmap(NULL, sizeof(shm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  do
  {
    sem_wait(&shared_memory->sem1_);
    strcpy(request, shared_memory->buf);
    printf("Hey pal, got your message. I will read it out loud.\n");
    
    for(int i = 0; i < sizeof(request); i++)
    {
      printf("%c", request[i]);
    }

    printf("Btw, there is a number stored in the shared quantum space.\n");
    // int num = 1;
    // shared_memory->number_ = num;
    // printf("Overwriting sucessfull\n");
    printf("This is the number: %d\n", shared_memory->number_);
    printf("Printing number successfull (or not?). I will now venture into the quantum space of dispatcher.\n");
    strcpy(response, dispatcher(shared_memory));
    printf("[Process2] %s\n", response);
    sem_post(&shared_memory->sem2_);

    fflush(stdin);

  } while (strcmp(shared_memory->buf, "bye\n") != 0);

  printf("Process2 is done\n");

  munmap(shared_memory, sizeof(shm));

  shm_unlink("/test");
}


char *dispatcher(shm *shared_memory)
{
  // TODO Student START
  // respond to the incoming questions

  printf("I'm in the quantum space of the dispatcher. Over.\n");

  printf("This is your message. I will read it out loud.\n");
    
  for(int i = 0; i < sizeof(request); i++)
  {
    printf("%c", shared_memory->buf[i]);
  }

  printf("This is the motvational number: %d\n", shared_memory->number_);

  if (strcmp(shared_memory->buf, predefines[7]) == 0) {
    int num = 1;
    shared_memory->number_ = num;
    return predefines[13];
  } else if (strcmp(shared_memory->buf, predefines[8]) == 0) {
    int num = 0;
    printf("This is the old number: %d\n", shared_memory->number_);
    shared_memory->number_ = num;
    printf("This is the new number: %d\n", shared_memory->number_);
    return predefines[13];
  }

  printf("I couldn't get into the sub-space of motivational interference. Over.\n");

  if (strcmp(shared_memory->buf, predefines[6]) == 0)
    return predefines[6];
  
  printf("Also couldn't get into the sub-space of Sayonara. Over.\n");

  // PROCESS STOPS HERE. WHY?
  // IT WORKS AGAIN. HAD TO GIVE EVERY SHARED MEMORY READ/WRITE PERMISSON

  if (shared_memory->number_ == 1) {

    printf("Entered the imaginary space of decisions. Over.\n");

    if (strcmp(shared_memory->buf, predefines[0]) == 0)
      return predefines[12];
    else if (strcmp(shared_memory->buf, predefines[1]) == 0)
      return predefines[9];
    else if (strcmp(shared_memory->buf, predefines[2]) == 0)
      return (predefines[11]);
    else if (strcmp(shared_memory->buf, predefines[3]) == 0)
      return predefines[11];
    else if (strcmp(shared_memory->buf, predefines[4]) == 0)
      return (predefines[10]);
    else if (strcmp(shared_memory->buf, predefines[5]) == 0)
      return predefines[10];

  } else if (shared_memory->number_ == 0) {

    printf("Attention. Motivation plummeted in the imaginary space. Over.\n");

    if (strcmp(shared_memory->buf, predefines[0]) == 0)
      return predefines[9];
    else if (strcmp(shared_memory->buf, predefines[1]) == 0)
      return predefines[11];
    else if (strcmp(shared_memory->buf, predefines[2]) == 0)
      return (predefines[9]);
    else if (strcmp(shared_memory->buf, predefines[3]) == 0)
      return predefines[11];
    else if (strcmp(shared_memory->buf, predefines[4]) == 0)
      return (predefines[12]);
    else if (strcmp(shared_memory->buf, predefines[5]) == 0)
      return predefines[10];
  } 

  printf("Mission failed. Gonna return with nothing. Exit with 'I don't understand'. Over.\n");

  // TODO Student END
  return predefines[13];
}