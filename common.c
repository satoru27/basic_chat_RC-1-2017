#include "common.h"

int serverSocket = -1;
int clientSocket = -1;

int handle_error(char *message){
  printf("------------------------------------\n");
  printf("[!] Program has encountered the following error:\n%s", message);
  printf("[!] Exiting...\n");
  if(clientSocket > -1){
    close(clientSocket);
    printf("[!] Closed client socket\n");
  }
  if(serverSocket > -1){
    close(serverSocket);
    printf("[!] Closed server socket\n");
  }
  exit(1);
}

void timeout_error(){
  printf("------------------------------------\n");
  printf("[!] Program has timed out\n");
  printf("[!] Exiting...\n");
  if(clientSocket > -1){
    close(clientSocket);
    printf("[!] Closed client socket\n");
  }
  if(serverSocket > -1){
    close(serverSocket);
    printf("[!] Closed server socket\n");
  }
  exit(1);
}
