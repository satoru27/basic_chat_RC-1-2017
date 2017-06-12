#include "server.h"

int run_tcp_server(long int port){

  int serverSocket; //socket descriptor for server
  int clientSocket; //socket descriptor for client
  struct sockaddr_in echoServerAddress; //local adress
  struct sockaddr_in echoClientAddress; //client address
  unsigned int clientLen; //length of client address data structure
  char buffer[256];
  int rw_flag;

  printf("[.] RUNNING TCP SERVER\n");
  //creating a TCP socket
  if( (serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    handle_error("[!] socket() failed");
  printf("[*] Socket created \n");

  //construct local address structure
  memset(&echoServerAddress, 0, sizeof(echoServerAddress));
  echoServerAddress.sin_family = AF_INET;
  echoServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  echoServerAddress.sin_port = htons((unsigned short) port);
  //Assign a port to a socket
  if((bind(serverSocket, (struct sockaddr *) &echoServerAddress, sizeof(echoServerAddress))) < 0)
    handle_error("[!] bind() failed\n");
  printf("[*] Bind successful \n");

  //Set socket to listen
  printf("[*] Waiting for connection... \n");
  listen(serverSocket,1); //set to 1 the maximum length to which the queue of pending connections for sockfd may grow
  clientLen = sizeof(echoClientAddress);

  if( (clientSocket = accept(serverSocket,(struct sockaddr *) &echoClientAddress,&clientLen)) < 0 )
    handle_error("[!] accept() failed");
  printf("[*] Connection accepted \n");

  for(;;){
    bzero(buffer,256);
    if((rw_flag = read(clientSocket,buffer,255))<0)
      handle_error("[!] read() failed");
    printf("[*] Received the following message: %s", buffer);
    printf("[*] Sending ACK\n");

    if((rw_flag = write(clientSocket,"[S] Got your message",21))<0)
      handle_error("[!] write() failed");


  }
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
    printf("------------------------------------\n");
    bzero(buf,1024);
    printf("[*] Waiting for message\n");
    if ((n = recvfrom(serverSocket,buf,1024,0,(struct sockaddr *) &client,&fromlength)) < 0 )
      handle_error("[!] recvfrom() failed");

/*
    if(time() > start + SERVER_TIMEOUT){
        handle_error("[!] SERVER_TIMEOUT on recv");
    }
*/
    printf("[S] Received a datagram: ");
    printf("%s",buf);

    if ( (n = sendto(serverSocket,"[S] Got your message",21,0,(struct sockaddr *)&client,fromlength)) < 0 )
      handle_error("[!] sendto() failed");
    printf("[*] ACK sent \n");
/*
    if(time() > start + SERVER_TIMEOUT){
        handle_error("[!] SERVER_TIMEOUT on sendto");
    }
*/


  }

return 0;

}
