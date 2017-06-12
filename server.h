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

#define SERVER_TIMEOUT 10
//int run_server(long int port,char *protocol);

int run_tcp_server(long int port);

int run_udp_server(long int port);

int print_received_message();


/*timeout
time_t start = time();
for (;;) {
    // try something
    if (time() > start + 5) {
        printf("5s timeout!\n");
        break;
    }
}
 */
