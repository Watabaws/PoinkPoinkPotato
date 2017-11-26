#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <errno.h>


int main(){
  srand(time(NULL));
  int ftos[2];
  int stof[2];

  printf("Creating pipe that the parent will use to send a number to the child\n");
  pipe(ftos);
  printf("Creating pipe that the child will use to send back the mathed number\n");
  pipe(stof);

  printf("Forking\n");
  if(fork()){
    close(ftos[0]);
    close(stof[1]);


    int send_num = 42; //rand();
    printf("Sending number %d to child -parent\n", send_num);
    write(ftos[1], &send_num, sizeof(send_num));
    printf("%s !!!!!!!!!!!!!!\n", strerror(errno));
    printf("Waiting for child to send back number\n");

    int status;
    wait(&status);

    int new_num;
    read(stof[0], &new_num, sizeof(new_num));
    printf("Received new number %d from the child -parent\n", new_num);
  }
  else{
    close(ftos[1]);
    close(stof[0]);

    int rec_num;
    read(ftos[0], &rec_num, sizeof(rec_num));

    printf("%s !!!!!!!!!!!!!!\n", strerror(errno));
    printf("Received number %d from parent -child\n", rec_num);

    printf("Adding 4, subtracting 3 and multiplying the number by 56 and sending it back -child\n");
    rec_num += 4;
    rec_num -= 3;
    rec_num *= 56;

    write(stof[1], &rec_num, sizeof(rec_num));

  }
}
