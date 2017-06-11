#include "server.h"

int handle_error(char *message){
  printf("------------------------------------\n");
  printf("[!] Program has encountered the following error:\n%s", message);
  printf("[!] Exiting...\n");
  exit(1);
}

int run_tcp_server(long int port){

  int serverSocket; //socket descriptor for server
  int clientSocket; //socket descriptor for client
  struct sockaddr_in echoServerAddress; //local adress
  struct sockaddr_in echoClientAddress; //client address
  unsigned short echoServerPort = (unsigned short) port; //server port
  unsigned int clientLen; //length of client address data structure

  printf("[.] RUNNING TCP SERVER\n");
  //creating a TCP socket
  if( (serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    handle_error("[!] socket() failed");

  //construct local address structure
  memset(&echoServerAddress, 0, sizeof(echoServerAddress));
  echoServerAddress.sin_family = AF_INET;
  echoServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  echoServerAddress.sin_port = htons(echoServerPort);
  //Assign a port to a socket
  //Set socket to listen
  //loop
  //Accept new connection
  //Communicate
  //Close the connection
  return 0;

}

int run_udp_server(long int port){
  //create a UDP socket
  int serverSocket,fromlength,n;
  struct sockaddr_in server;
  struct sockaddr_in client;
  char buf[1024];

  printf("[.] RUNNING UDP SERVER\n");

  if( (serverSocket = socket(AF_INET, SOCK_DGRAM,0)) < 0)
    handle_error("[!] socket() failed\n");
  printf("[*] Socket created \n");

  memset(&server, 0, sizeof(server));
  server.sin_family=AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port=htons((unsigned short) port);

  //assign a port to socket
  if (bind(serverSocket,(struct sockaddr *) &server,sizeof(server) )<0)
    handle_error("[!] bind() failed\n");
  printf("[*] Bind successful \n");

  //Communicate
  fromlength = sizeof(struct sockaddr_in);

  //time_t start = time();

  for(;;){

    printf("[*] Waiting for message\n");
    if ((n = recvfrom(serverSocket,buf,1024,0,(struct sockaddr *) &client,&fromlength)) < 0 )
      handle_error("[!] recvfrom() failed");

/*
    if(time() > start + SERVER_TIMEOUT){
        handle_error("[!] SERVER_TIMEOUT on recv");
    }
*/
    write(1,"[S] Received a datagram: ",21);
    write(1,buf,n);

    if ( (n = sendto(serverSocket,"[S] Got you message\n",17,0,(struct sockaddr *)&client,fromlength)) < 0 )
      handle_error("[!] sendto() failed");
    printf("[*] Message sent \n");
/*
    if(time() > start + SERVER_TIMEOUT){
        handle_error("[!] SERVER_TIMEOUT on sendto");
    }
*/

    return 0;
  }



}
