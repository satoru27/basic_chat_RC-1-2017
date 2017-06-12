#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include "common.h"
#define CLIENT_TIMEOUT 10

int run_tcp_client(char *host, long int port);
int run_udp_client(char *host, long int port);
int handle_error(char *message);
