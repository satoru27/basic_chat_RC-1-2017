#include "server.h"
#include "client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  char *mode,*protocol = "-u";
  long int temp,port = 33333;

  switch(argc){

    case 1:
    printf("[!] More arguments are needed, exiting...\n");
    return -1;

    case 2:
    if(strcmp(argv[1],"-S")!=0 && strcmp(argv[1],"host")!=0){
      printf("[!] Invalid mode, exiting...\n");
      return -1;
    }
      mode=argv[1];
      break;

    case 3:
    if(strcmp(argv[1],"-S")!=0 && strcmp(argv[1],"host")!=0 ){
      printf("[!] Invalid mode, exiting...\n");
      return -1;
    }
    mode=argv[1];
    temp = strtol(argv[2],NULL,0);
    if(temp < 1024){
      printf("[!] Invalid port, default port (33333) was selected\n");
    }
    else{
    port=temp;
    }
    break;

    case 4:

    if(strcmp(argv[1],"-S")!=0 && strcmp(argv[1],"host")!=0 ){
      printf("[!] Invalid mode, exiting...\n");
      return -1;
    }
    mode=argv[1];

    temp = strtol(argv[2],NULL,0);

    if(temp < 1024){
      printf("[!] Invalid port, default port (33333) was selected\n");
    }
    else{
    port=temp;
    }

    if(strcmp(argv[3],"-t")!=0 && strcmp(argv[3],"-u")!=0){
      printf("[!] Invalid selected protocol, using default protocol (UDP)\n");
    }
    else{
      protocol = argv[3];
    }
    break;

    }

  if(strcmp(mode,"-S")==0){
    printf("[.] Operating mode: server\n");
  }
  else{
    printf("[.] Operating mode: host\n");
  }

  printf("[.] Port: %li\n",port);

  if(strcmp(protocol,"-t")==0){
    printf("[.] Protocol: TCP\n");
  }
  else{
    printf("[.] Protocol: UDP\n");
  }

  return 0;

}
