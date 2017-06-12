#include "common.h"

int handle_error(char *message){
  printf("------------------------------------\n");
  printf("[!] Program has encountered the following error:\n%s", message);
  printf("[!] Exiting...\n");
  exit(1);
}
