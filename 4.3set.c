#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
 int sockd,newsockd,c;
 struct sockaddr_in server, client;
 char *message;
 int optval;
 socklen_t optlen = sizeof(optval);

 sockd = socket(AF_INET,SOCK_STREAM,0);
 if(sockd==-1)
 {
  printf("Create socket failed\n");
 }
 if(getsockopt(sockd,SOL_SOCKET,SO_KEEPALIVE,&optval,&optlen)<0)
 {
  perror("getsockopt()");
  close(sockd);
  exit(EXIT_FAILURE);
 }
 printf("SO_KEEPALIVE is %s\n",(optval ?"ON":"OFF"));

 optval = 1;
 optlen = sizeof(optval);
 if(setsockopt(sockd,SOL_SOCKET,SO_KEEPALIVE,&optval,optlen)<0)
 {
  perror("setsockopt()");
  close(sockd);
  exit(EXIT_FAILURE);
 }
 printf("SO_KEEPALIVE set on socket\n");

 if(getsockopt(sockd, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) 
 {
 perror("getsockopt()");
 close(sockd);
 exit(EXIT_FAILURE);
 }
 printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
 server.sin_port = htons( 8888 );
 //Bind
 if( bind(sockd,(struct sockaddr *)&server , sizeof(server)) < 0)
 {
  puts("bind failed");
  return 1;
 }
 puts("bind done");
 listen(sockd , 3);

 //Accept and incoming connection
 puts("Waiting for incoming connections...");
 c = sizeof(struct sockaddr_in);
 while( (newsockd = accept(sockd, (struct sockaddr *)&client, (socklen_t*)&c)) )
 {
  puts("Connection accepted");
  //Reply
  message = "Hello Client , I have received your connection. But I have to go now, bye\n";
  write(newsockd , message , strlen(message));
 }
 if (newsockd<0)
 {
  perror("accept failed");
  return 1;
 }
 return 0;

}
