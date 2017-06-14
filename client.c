#include "client.h"

int run_tcp_client(char *host,long int port){
  //clientSocket is defined globally on common.h
  printf("[.] RUNNING TCP CLIENT\n");
  int rw_flag;
  struct sockaddr_in server_addr;
  struct hostent *server;
  char buffer[256];
  int close_flag = 0;

  signal(SIGALRM,&timeout_error);

  if( (clientSocket = socket(AF_INET,SOCK_STREAM,0)) < 0)
    handle_error("[!] socket() failed\n");
  printf("[*] Socket created \n");

  if((server = gethostbyname(host)) == NULL)
    handle_error("[!] Unknown host\n");
  printf("[*] Host found \n");

  bzero((char *) &server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;

  bcopy((char *) server->h_addr,(char *)&server_addr.sin_addr.s_addr,server->h_length);

  server_addr.sin_port = htons((unsigned short) port);

  alarm(TIMEOUT);
  if((connect(clientSocket,&server_addr,sizeof(server_addr))) < 0)
    handle_error("[!] connect() error \n");
  printf("[*] Connection successful\n");

  for(;;){
    printf("------------------------------------\n");
    bzero(buffer,256);
    printf("[*] Enter the message to be sent: > ");
    fgets(buffer,255,stdin);


    alarm(TIMEOUT);
    if((rw_flag = write(clientSocket,buffer,strlen(buffer))) < 0)
      handle_error("[!] write() error \n");
    printf("[*] Write successful\n");

    close_flag = strcmp(buffer,"close()\n");

    alarm(TIMEOUT);
    bzero(buffer,256);
    if((rw_flag = read(clientSocket,buffer,255)) < 0)
      handle_error("[!] read() error \n");
    printf("[*] ACK received: ");
    printf("%s\n", buffer);

    if(close_flag == 0){
      printf("[*] Ending connection with server\n");
      break;
    }

  }
  close(clientSocket);
  printf("[*] Client socket closed\n");
  return 0;
}


int run_udp_client(char *host, long int port){
  //clientSocket is defined globally on common.h
  printf("[.] RUNNING UDP CLIENT\n");

  int length, n;
  struct sockaddr_in server, from;
  struct hostent *hp;
  char buffer[256];

  signal(SIGALRM,&timeout_error);

  if( (clientSocket = socket(AF_INET, SOCK_DGRAM,0)) < 0)
    handle_error("[!] socket() failed\n");
  printf("[*] Socket created \n");

  server.sin_family = AF_INET;

  if((hp = gethostbyname(host))==NULL)
    handle_error("[!] Unknown host\n");
  printf("[*] Host found \n");

  bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
  server.sin_port = htons((unsigned short) port);
  length = sizeof(struct sockaddr_in);

  printf("[*] Enter message to be sent: > ");
  bzero(buffer,256);
  fgets(buffer,255,stdin);

  alarm(TIMEOUT);
  if( (n = sendto(clientSocket,buffer,strlen(buffer),0,&server,length)) < 0)
    handle_error("[!] sendto() failed");

  alarm(TIMEOUT);
  if( (n = recvfrom(clientSocket,buffer,256,0,&from,&length)) < 0)
    handle_error("[!] recvfrom() failed");

  printf("[*] ACK received: ");
  printf("%s\n",buffer);

  close(clientSocket);
  printf("[*] Client socket closed\n");

  return 0;
}
