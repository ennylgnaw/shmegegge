#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main() {
  
  key_t key;
  int shmid;
  char *data;

  key = ftok("file",'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);

  if (data[0])
    printf("Contents of shared memory: %s\n", data);
  else
    printf("Segment just created!\n");

  char input[200];
  printf("Do you want to change the data in the string? y or n?\n");
  fgets(input, 200, stdin);

  if (!strcmp(input, "y\n")) {
    printf("Enter a new string to be stored: \n");
    fgets(input, 200, stdin);
    input[strlen(input) - 1] = 0;
    strcpy(data, input);
  }

  printf("Do you want to delete the segment? y or n?\n");
  fgets(input, 200, stdin);
  if (!strcmp(input, "y\n")) {
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Segment deleted.\n");
  }

  return 0;
  
}
