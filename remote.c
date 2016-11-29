/*  remote.c */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>


// Program to act as the remote user, issuing commands to the Host (malware)
int main(int argc, char *argv[]) {

  int sock, written;
  struct sockaddr_in host;
  
  char *addr = "127.0.0.1";
  short port = 8888;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("Creation of Socket: Failed\n");
    exit(0);
  }
  printf("Creation of Socket: Success\n");
  
  host.sin_addr.s_addr = inet_addr(addr);
  host.sin_family = AF_INET;
  host.sin_port = htons(port);

  //Connect to open port on the Host machine
  if (connect(sock, (struct sockaddr *) &host, sizeof(host)) < 0) {
    perror("Connection to Host: Failed\n");
    exit(0);
  }
  printf("Connection to Host: Success\n");


  //TEST: sending message to Host
  char message[200];
  printf("Enter cmd: \n");
  scanf("%s", message);

  if ((written = write(sock, message, strlen(message))) <= 0) {
    printf("Writing message to Socket: Failed\n");
    close(sock);
    exit(0);
  }
  printf("Delivered message: %s\n", &message);
  

  //Cleanup
  close(sock);
  return 0;
}
