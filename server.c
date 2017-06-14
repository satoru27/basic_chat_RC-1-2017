#include "server.h"

int run_tcp_server(long int port){
  //clientSocket and serverSocket are defined globally on common.h
  struct sockaddr_in echoServerAddress; //local adress
  struct sockaddr_in echoClientAddress; //client address
  unsigned int clientLen; //length of client address data structure
  char buffer[256];
  int rw_flag;
  int close_flag = 0;

  signal(SIGALRM,&timeout_error);//setting a signal for a possible timeout event

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

  for(;;){//loop
    //Set socket to listen
    printf("[*] Waiting for connection... \n");
    alarm(TIMEOUT);//alarm is set for every possible blocking call
    listen(serverSocket,1); //set to 1 the maximum length to which the queue of pending connections for sockfd may grow
    clientLen = sizeof(echoClientAddress);

    //Accept new connection
    alarm(TIMEOUT);
    if( (clientSocket = accept(serverSocket,(struct sockaddr *) &echoClientAddress,&clientLen)) < 0 )
      handle_error("[!] accept() failed");
    printf("[*] Connection accepted \n");

    for(;;){  //Communicate
      printf("------------------------------------\n");
      bzero(buffer,256);//clears the message buffer

      alarm(TIMEOUT);
      if((rw_flag = read(clientSocket,buffer,255))<0)//read message sent from the client
        handle_error("[!] read() failed");
      printf("[*] Received the following message: %s", buffer);
      printf("[*] Sending ACK\n");

      //if the message sent is "close()" (with a newline that is needed to sent the message)
      //the server will begin to close the connection with the client
      close_flag = strcmp(buffer,"close()\n");

      alarm(TIMEOUT);
      if((rw_flag = write(clientSocket,"[S] Got your message",21))<0)
        handle_error("[!] write() failed");

      if(close_flag == 0){
        printf("[*] Ending connection with client\n");
        break;
        //after connection with the client ends, return to the listening loop
      }

    }
    close(clientSocket);//close the client socket
    printf("[*] Client socket closed\n");
  }

  close(serverSocket);//close the server socket
  printf("[*] Server socket closed\n");
  return 0;

}

int run_udp_server(long int port){
  //clientSocket and serverSocket are defined globally on common.h
  printf("[.] RUNNING UDP SERVER\n");

  //extern int serverSocket;
  int fromlength,n;
  struct sockaddr_in server;
  struct sockaddr_in client;
  char buf[1024];

  signal(SIGALRM,&timeout_error);

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

  for(;;){
    printf("------------------------------------\n");
    bzero(buf,1024);

    printf("[*] Waiting for message\n");
    alarm(TIMEOUT);
    if ((n = recvfrom(serverSocket,buf,1024,0,(struct sockaddr *) &client,&fromlength)) < 0 )
      handle_error("[!] recvfrom() failed");

    printf("[S] Received a datagram: ");
    printf("%s",buf);

    alarm(TIMEOUT);
    if ( (n = sendto(serverSocket,"[S] Got your message",21,0,(struct sockaddr *)&client,fromlength)) < 0 )
      handle_error("[!] sendto() failed");
    printf("[*] ACK sent \n");


  }
close(serverSocket);
printf("[*] Closed server socket\n");
return 0;

}
